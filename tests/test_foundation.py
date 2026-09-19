import copy
import json
import struct
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from common import ROOT, FormatError, Reader, fixture, read_json, sha256
import ne, mapsym, omf
from analysis import extent
from compiler import compile_source, validate_receipt, verify_lock
from matcher import compare, unique_symbol

def record(kind,body):
    raw=bytes([kind])+struct.pack('<H',len(body)+1)+body
    return raw+bytes([-sum(raw)&255])

def pstr(text):return bytes([len(text)])+text.encode()

def synthetic(payload=b'\x9a\0\0\0\0\xcb',fixup=b'\xcc\x01\x56\x01',iterated=False):
    parts=[record(0x80,pstr('test.c')),record(0x96,pstr('TEXT')+pstr('CODE')+pstr('')),
           record(0x98,b'\x68'+struct.pack('<H',6)+b'\x01\x02\x03'),
           record(0x90,b'\0\1'+pstr('_Test')+b'\0\0\0'),record(0x8c,pstr('_Callee')+b'\0'),
           record(0xa2 if iterated else 0xa0,b'\1\0\0'+payload)]
    if fixup is not None:parts.append(record(0x9c,fixup))
    return b''.join(parts)+record(0x8a,b'\0')

class ParserTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.exe=fixture('SIMANTW.EXE');cls.sym=fixture('SIMANTW.SYM')
        cls.n=ne.parse(cls.exe);cls.s=mapsym.parse(cls.sym)

    def test_ne_known_header_and_layout(self):
        self.assertEqual(self.n['header']['linker_version'],'5.30')
        self.assertEqual(self.n['header']['target_os'],2)
        self.assertEqual(len(self.n['segments']),10)
        self.assertEqual(sum(len(r['sites']) for s in self.n['segments'] for r in s['relocations']),8145)
        self.assertEqual(self.n['header']['cs'],4)
        self.assertEqual(self.n['header']['ip'],97)

    def test_ne_truncation(self):
        for length in [0,63,1050,2048,len(self.exe)//2]:
            with self.assertRaises(FormatError):ne.parse(self.exe[:length])

    def test_ne_bad_signature(self):
        b=bytearray(self.exe);b[1024]=0
        with self.assertRaises(FormatError):ne.parse(b)

    def test_relocation_chain_cycle(self):
        b=bytearray(self.exe);s=self.n['segments'][0];r=s['relocations'][0];site=r['sites'][0]
        struct.pack_into('<H',b,s['file_offset']+site,site)
        with self.assertRaises(FormatError):ne.parse(b)

    def test_resources_complete_and_bounded(self):
        self.assertEqual(len(self.n['resources']),41)
        self.assertEqual({r['type_name'] for r in self.n['resources']},{'GROUP_ICON','ICON','GROUP_CURSOR','CURSOR','DIALOG','ACCELERATOR'})
        for r in self.n['resources']:self.assertEqual(sha256(self.exe[r['offset']:r['offset']+r['size']]),r['sha256'])

    def test_resource_outside_file(self):
        b=bytearray(self.exe);struct.pack_into('<H',b,self.n['resources'][0]['table_offset'],65535)
        with self.assertRaises(FormatError):ne.parse(b)

    def test_mapsym_inventory(self):
        self.assertEqual(self.s['version'],'3.10')
        self.assertEqual(sum(len(x['symbols']) for x in self.s['segments']),2171)
        self.assertEqual(len(self.s['absolute_symbols']),20)
        self.assertEqual(unique_symbol(self.s,'_StopSimulation'),(1,0))
        self.assertEqual(unique_symbol(self.s,'__astart'),(4,97))

    def test_mapsym_link_cycle(self):
        b=bytearray(self.sym);p=self.s['segments'][0]['file_offset'];struct.pack_into('<H',b,p,p//16)
        with self.assertRaises(FormatError):mapsym.parse(b)

    def test_mapsym_invalid_pointer_and_version(self):
        for pos in [len(self.sym)-1,self.s['segments'][0]['file_offset']+4]:
            b=bytearray(self.sym);b[pos]=255
            with self.assertRaises(FormatError):mapsym.parse(b)

    def test_symbol_pair_and_wrong_export(self):
        self.assertEqual(mapsym.cross_check(self.s,self.n)['status'],'STRUCTURALLY_CONSISTENT')
        bad=copy.deepcopy(self.s)
        for s in bad['segments']:
            for x in s['symbols']:
                if x['name']=='MAINWNDPROC':x['offset']+=1
        with self.assertRaises(FormatError):mapsym.cross_check(bad,self.n)

    def test_wrong_symbol_resolution(self):
        with self.assertRaises(FormatError):unique_symbol(self.s,'_DefinitelyMissing')

    def test_extent_branch_arms_and_padding(self):
        e=extent(bytes.fromhex('7401cbc b90'.replace(' ','')),0,5)
        self.assertEqual(e['size'],4)
        self.assertEqual(len(e['return_offsets']),2)

    def test_extent_indirect_jump_unconfirmed(self):
        self.assertIsNone(extent(bytes.fromhex('ffe090cb'),0,4)['end'])

    def test_omf_public_and_fixup(self):
        m=omf.parse(synthetic());self.assertEqual(m['publics'][0]['name'],'_Test')
        f=m['fixups'][0];self.assertEqual((f['offset'],f['width'],f['frame_method']),(1,4,5))
        self.assertEqual(f['target'],{'kind':'external','name':'_Callee'})

    def test_omf_threads(self):
        # target thread 0 = external 1; frame thread 0 = target; use both.
        m=omf.parse(synthetic(fixup=b'\x08\x01\x54\xcc\x01\x8c'))
        self.assertEqual(m['fixups'][0]['target']['name'],'_Callee')

    def test_omf_undefined_thread(self):
        with self.assertRaises(FormatError):omf.parse(synthetic(fixup=b'\xcc\x01\x8c'))

    def test_omf_lidata(self):
        m=omf.parse(synthetic(payload=b'\x03\0\0\0\x02\xaa\xbb',fixup=None,iterated=True))
        self.assertEqual(m['segments'][0]['data_hex'],'aabbaabbaabb')

    def test_omf_lidata_fixup_fails_closed(self):
        with self.assertRaises(FormatError):omf.parse(synthetic(payload=b'\x03\0\0\0\x02\xaa\xbb',iterated=True))

    def test_omf_checksum_and_unknown_record(self):
        b=bytearray(synthetic());b[5]^=1
        with self.assertRaises(FormatError):omf.parse(b)
        with self.assertRaises(FormatError):omf.parse(record(0xfe,b'\0'))

    def test_omf_truncation(self):
        for end in [1,4,len(synthetic())-1]:
            with self.assertRaises(FormatError):omf.parse(synthetic()[:end])

class CompilerMatcherTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.raw=fixture('SIMANTW.EXE');cls.ne=ne.parse(cls.raw);cls.sym=mapsym.parse(fixture('SIMANTW.SYM'))
        recipes=read_json(ROOT/'src/recovery.json')['targets']
        cls.targets={name:recipes[name] for name in ('_ABS','_InitApplicationStuff','_CountUpdate')};cls.objects={};cls.receipts={}
        for name,t in cls.targets.items():
            p,r=compile_source(t['source'],t['flags'],t.get('compiler','msc600a'));cls.objects[name]=omf.parse(p.read_bytes());cls.receipts[name]=r

    def check(self,name,obj=None,target=None):
        return compare(obj or self.objects[name],self.raw,self.ne,self.sym,dict(target or self.targets[name],symbol=name))

    def test_three_fresh_matches(self):
        for name in self.targets:self.assertEqual(self.check(name)['result'],'FUNCTION_MATCH')

    def test_changed_instruction(self):
        m=copy.deepcopy(self.objects['_ABS']);b=bytearray.fromhex(m['segments'][0]['data_hex']);b[13]=0xd0;m['segments'][0]['data_hex']=b.hex()
        self.assertNotEqual(self.check('_ABS',m)['result'],'FUNCTION_MATCH')

    def test_wrong_relocation_target(self):
        m=copy.deepcopy(self.objects['_InitApplicationStuff']);m['fixups'][0]['target']['name']='_Feedback'
        self.assertNotEqual(self.check('_InitApplicationStuff',m)['result'],'FUNCTION_MATCH')

    def test_wrong_frame_and_missing_fixup(self):
        for alteration in ['frame','missing']:
            m=copy.deepcopy(self.objects['_InitApplicationStuff'])
            if alteration=='frame':m['fixups'][0]['frame_method']=4
            else:m['fixups']=[]
            self.assertNotEqual(self.check('_InitApplicationStuff',m)['result'],'FUNCTION_MATCH')

    def test_wrong_candidate_public_and_segment(self):
        for key in ['public','segment']:
            m=copy.deepcopy(self.objects['_ABS'])
            if key=='public':m['publics'][0]['name']='_Other'
            else:m['segments'][0]['name']='WRONG'
            with self.assertRaises(FormatError):self.check('_ABS',m)

    def test_wrong_length(self):
        m=copy.deepcopy(self.objects['_InitApplicationStuff']);s=m['segments'][0];s['data_hex']='90'+s['data_hex'];s['length']+=1;s['initialized_ranges']=[[0,s['length']]]
        for f in m['fixups']:f['offset']+=1
        self.assertNotEqual(self.check('_InitApplicationStuff',m)['result'],'FUNCTION_MATCH')

    def test_wrong_manifest_segment_or_extent(self):
        for field in ['segment','size']:
            target=dict(self.targets['_ABS']);target[field]+=1
            with self.assertRaises(FormatError):self.check('_ABS',target=target)

    def test_wrong_tool_hash(self):
        lock=read_json(ROOT/'layout/toolchain.json');lock['files'][lock['runner']]['sha256']='0'*64
        with self.assertRaises(FormatError):verify_lock(lock)

    def test_stale_receipts(self):
        for key in ['source_identity','object_identity']:
            r=copy.deepcopy(self.receipts['_ABS']);r[key]['sha256']='0'*64
            with self.assertRaises(FormatError):validate_receipt(r)
        r=copy.deepcopy(self.receipts['_ABS']);r['toolchain_lock_sha256']='0'*64
        with self.assertRaises(FormatError):validate_receipt(r)

    def test_compilation_reads_no_fixtures(self):
        original=Path.read_bytes
        def guarded(path):
            if path.resolve().is_relative_to(ROOT/'assets'):raise AssertionError('construction touched fixtures')
            return original(path)
        with patch.object(Path,'read_bytes',guarded):compile_source('src/abs.c',self.targets['_ABS']['flags'])

if __name__=='__main__':unittest.main()
