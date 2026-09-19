import sys,copy,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from common import ROOT,fixture,FormatError
import ne,mapsym,omf
from library_match import compare_member,import_symbols
from fp_fingerprint import check_fidr

class FloatingFixupTests(unittest.TestCase):
 @classmethod
 def setUpClass(cls):
  cls.raw=fixture('SIMANTW.EXE');cls.image=ne.parse(cls.raw)
 def test_original_fp_instruction_and_fixup(self):
  self.assertTrue(check_fidr(self.raw,self.image,1,0x1b35,bytes.fromhex('9bdb46dc')))
 def test_wrong_fixup_type_or_missing_obligation(self):
  for mutation in ('type','missing','additive'):
   n=copy.deepcopy(self.image);ss=n['segments'][0]
   r=next(r for r in ss['relocations'] if 0x1b35 in r['sites'])
   if mutation=='type':r['target']['type']=4
   elif mutation=='missing':ss['relocations'].remove(r)
   else:r['additive']=False
   self.assertFalse(check_fidr(self.raw,n,1,0x1b35,bytes.fromhex('9bdb46dc')))
 def test_fixup_must_not_hide_instruction_change(self):
  raw=bytearray(self.raw);raw[self.image['segments'][0]['file_offset']+0x1b36]^=1
  self.assertFalse(check_fidr(raw,self.image,1,0x1b35,bytes.fromhex('9bdb46dc')))

class CompleteMemberTests(unittest.TestCase):
 @classmethod
 def setUpClass(cls):
  cls.raw=fixture('SIMANTW.EXE');cls.ne=ne.parse(cls.raw);cls.sym=mapsym.parse(fixture('SIMANTW.SYM'))
  cls.imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB');cls.members={}
  for data in omf.library_modules((ROOT/'toolchain/sdk300/CLIB/LLIBCW.LIB').read_bytes()):
   try:m=omf.parse(data)
   except FormatError:continue
   cls.members[m['name']]=m
 def check_member(self,m):return compare_member(m,self.raw,self.ne,self.sym,self.imports)
 def test_complete_startup_and_fopen(self):
  for name in ['windows\\winstart.asm','fopen.c','malloc.asm','free.asm']:
   self.assertEqual(self.check_member(self.members[name])['result'],'CONFIRMED_MEMBER')
 def test_rand_entire_code_and_private_data(self):
  r=self.check_member(self.members['rand.c'])
  self.assertEqual(r['result'],'STRONGLY_SUPPORTED_MEMBER')
  self.assertEqual([(x['segment'],x['length']) for x in r['contributions']],[('_TEXT',68),('_DATA',4)])
 def test_second_function_mutation_not_hidden_by_first_match(self):
  m=copy.deepcopy(self.members['rand.c']);ss=m['segments'][0];b=bytearray.fromhex(ss['data_hex']);b[24]^=1;ss['data_hex']=b.hex()
  self.assertEqual(self.check_member(m)['result'],'NO_COMPLETE_MATCH')
 def test_private_seed_mutation(self):
  m=copy.deepcopy(self.members['rand.c']);m['segments'][1]['data_hex']='02000000'
  self.assertEqual(self.check_member(m)['result'],'NO_COMPLETE_MATCH')
 def test_far_translation_target_and_frame_are_checked(self):
  for field in ('target','frame'):
   m=copy.deepcopy(self.members['rand.c']);f=next(f for f in m['fixups'] if f['location_type']==3)
   if field=='target':f['target']['name']='_free'
   else:f['frame_method']=4
   self.assertEqual(self.check_member(m)['result'],'NO_COMPLETE_MATCH')
 def test_conflicting_public_anchors_reject(self):
  m=copy.deepcopy(self.members['rand.c']);m['publics'][1]['offset']+=2
  self.assertEqual(self.check_member(m)['result'],'RULED_OUT_MEMBER')
 def test_missing_loader_fixup_reject(self):
  m=copy.deepcopy(self.members['windows\\winstart.asm']);m['fixups']=[f for f in m['fixups'] if f['target'].get('name')!='INITTASK']
  self.assertEqual(self.check_member(m)['result'],'NO_COMPLETE_MATCH')
 def test_import_binding_checked(self):
  imports=copy.deepcopy(self.imports);imports['INITTASK']['ordinal']+=1
  r=compare_member(self.members['windows\\winstart.asm'],self.raw,self.ne,self.sym,imports)
  self.assertEqual(r['result'],'NO_COMPLETE_MATCH')

class CompleteFloatingMemberTests(unittest.TestCase):
 @classmethod
 def setUpClass(cls):
  cls.raw=fixture('SIMANTW.EXE');cls.image=ne.parse(cls.raw);cls.sym=mapsym.parse(fixture('SIMANTW.SYM'))
  cls.imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')
  cls.members={}
  for b in omf.library_modules((ROOT/'toolchain/sdk300/CLIB/LLIBFPW.LIB').read_bytes()):
   m=omf.parse(b);cls.members[m['name'].split('\\')[-1].lower()]=m
 def compare(self,m,n=None):
  return compare_member(m,self.raw,n or self.image,self.sym,self.imports)
 def test_complete_fp_members(self):
  for name in ('87sqrt.asm','87ftol.asm','x8tmul.asm','tenpow.asm'):
   self.assertIn(self.compare(self.members[name])['result'],('CONFIRMED_MEMBER','STRONGLY_SUPPORTED_MEMBER'))
 def test_paired_fixup_cannot_be_missing_or_misframed(self):
  for action in ('remove','frame','displacement'):
   m=copy.deepcopy(self.members['x8tmul.asm']);f=next(f for f in m['fixups'] if f['target'].get('name')=='FJCRQQ')
   if action=='remove':m['fixups'].remove(f)
   elif action=='frame':f['frame_method']=0
   else:f['displacement']=1
   self.assertEqual(self.compare(m)['result'],'NO_COMPLETE_MATCH')
 def test_fp_opcode_bytes_are_not_masked(self):
  m=copy.deepcopy(self.members['87sqrt.asm']);f=next(f for f in m['fixups'] if f['target'].get('name')=='FIDRQQ')
  ss=m['segments'][f['segment']-1];b=bytearray.fromhex(ss['data_hex']);b[f['offset']+1]^=1;ss['data_hex']=b.hex()
  self.assertEqual(self.compare(m)['result'],'NO_COMPLETE_MATCH')
 def test_wrong_ne_fp_type_rejects_complete_member(self):
  m=self.members['87ftol.asm'];r=self.compare(m);n=copy.deepcopy(self.image)
  c=next(c for c in r['contributions'] if c['segment']=='_TEXT')
  f=next(f for f in m['fixups'] if f['target'].get('name')=='FIWRQQ')
  rr=next(x for x in n['segments'][c['original_segment']-1]['relocations'] if c['original_offset']+f['offset'] in x['sites'])
  rr['target']['type']=5
  self.assertEqual(self.compare(m,n)['result'],'NO_COMPLETE_MATCH')

class AdditionalOmfTests(unittest.TestCase):
 def test_empty_use32_metadata_segment(self):
  from test_foundation import synthetic,record
  b=synthetic(fixup=None);end=list(omf.records(b))[-1][0]
  m=omf.parse(b[:end]+record(0x99,b'\x21\0\0\0\0\x01\x02\x03')+b[end:])
  self.assertEqual(m['segments'][-1]['length'],0)
  with self.assertRaises(FormatError):omf.parse(b[:end]+record(0x99,b'\x21\1\0\0\0\x01\x02\x03')+b[end:])
 def test_alias_record(self):
  from test_foundation import synthetic,record
  b=synthetic(fixup=None);end=list(omf.records(b))[-1][0]
  m=omf.parse(b[:end]+record(0xc6,b'\x04_old\x04_new')+b[end:])
  self.assertEqual(m['aliases'],[{'alias':'_old','substitute':'_new'}])
 def test_backpatch_and_bounds(self):
  from test_foundation import synthetic,record
  b=synthetic(payload=b'\x90\x01\x00\x90\x90\xcb',fixup=None);end=list(omf.records(b))[-1][0]
  m=omf.parse(b[:end]+record(0xb2,b'\x01\x01\x01\x00\x02\x00')+b[end:])
  self.assertEqual(m['segments'][0]['data_hex'],'9003009090cb')
  with self.assertRaises(FormatError):omf.parse(b[:end]+record(0xb2,b'\x01\x01\xff\xff\x02\x00')+b[end:])

if __name__=='__main__':unittest.main()
