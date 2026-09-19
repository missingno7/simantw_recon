"""Independent executable evidence; no compiler output enters this census."""
from collections import Counter,defaultdict
from common import ROOT,fixture,write_json
from analysis import decoder,extent,cs
from capstone.x86 import X86_OP_MEM,X86_OP_IMM,X86_REG_DS,X86_REG_ES,X86_REG_CS
import ne,mapsym

def main():
 raw=fixture('SIMANTW.EXE');n=ne.parse(raw);s=mapsym.parse(fixture('SIMANTW.SYM'));out=[];all_examples=defaultdict(list)
 for sg in s['segments'][:7]:
  ns=n['segments'][sg['number']-1];code=raw[ns['file_offset']:ns['file_offset']+ns['logical_size']]
  reloc={q:r for r in ns['relocations'] for q in r['sites']};counts=Counter();seen=set();closed=0
  def hit(kind,i,name,detail=None):
   counts[kind]+=1
   if len(all_examples[kind])<12:all_examples[kind].append({'segment':sg['number'],'offset':i.address,'symbol':name,'bytes':i.bytes.hex(),'instruction':i.mnemonic+' '+i.op_str,'detail':detail})
  for sym in sg['symbols']:
   lim=min([x['offset'] for x in sg['symbols'] if x['offset']>sym['offset']]+[len(code)])
   e=extent(code,sym['offset'],lim)
   if not e['size']:continue
   closed+=1
   for i in decoder().disasm(code[sym['offset']:e['end']],sym['offset']):
    if i.address in seen:continue
    seen.add(i.address);counts['instructions']+=1
    if i.group(cs.CS_GRP_CALL):
     if i.mnemonic=='lcall':
      rr=next((reloc[q] for q in range(i.address,i.address+i.size) if q in reloc),None)
      hit('far_indirect_call' if i.operands[0].type==X86_OP_MEM else 'far_direct_call',i,sym['name'],rr['target'] if rr else None)
     elif i.operands[0].type==X86_OP_IMM:
      hit('relaxed_far_call' if code[i.address-2:i.address]==b'\x90\x0e' else 'near_direct_call',i,sym['name'],{'target':i.operands[0].imm})
     else:hit('near_indirect_call',i,sym['name'])
    if i.group(cs.CS_GRP_RET):hit(('far_' if i.mnemonic.startswith('retf') else 'near_')+('callee_pop_return' if i.operands else 'plain_return'),i,sym['name'])
    if i.mnemonic in ('les','lds'):hit(i.mnemonic+'_four_byte_pointer',i,sym['name'])
    if i.mnemonic in ('enter','leave') or i.bytes[0] in (0x68,0x6a,0xc0,0xc1):hit('186_or_later_instruction',i,sym['name'])
    # CDQ/CWDE are Capstone aliases even without 66h in 16-bit mode: don't count them.
    if 0x66 in i.prefix or 0x67 in i.prefix or any(op.size==4 for op in i.operands if op.type==1):hit('386_operand_or_address_evidence',i,sym['name'])
    if i.mnemonic=='int' and i.operands and 0x34<=i.operands[0].imm<=0x3d:hit('fp_emulator_interrupt',i,sym['name'])
    if i.mnemonic.startswith('f') and i.mnemonic!='fwait':hit('x87_instruction',i,sym['name'])
    for op in i.operands:
     if op.type!=X86_OP_MEM:continue
     if op.mem.segment==X86_REG_ES:hit('es_data_operand',i,sym['name'])
     if not op.mem.base and not op.mem.index and op.mem.segment in (0,X86_REG_DS):
      addr=op.mem.disp&65535;slot=next((r for r in n['segments'][9]['relocations'] if addr in r['sites'] and r['source_type']==2),None)
      if slot and i.mnemonic=='mov' and i.op_str.startswith(('es,','ds,')):hit('dgroup_far_selector_pool_load',i,sym['name'],{'pool_offset':addr,'target':slot['target']})
      else:hit('direct_ds_data_operand',i,sym['name'],{'offset':addr,'ds_equals_dgroup':'assumption; validated on selected probes and CRT'})
  out.append({'segment':sg['number'],'name':sg['name'],'closed_symbol_extents':closed,'unique_instructions':len(seen),'counts':dict(counts)})
 evidence={'exe_sha256':n['sha256'],'sym_sha256':s['sha256'],'scope':'Conservative closed contiguous CFGs only; excludes switch tables, undecoded bodies and padding. Counts are lower bounds; segment 4 is mixed CRT and handwritten utilities.',
  'segments':out,'examples':dict(all_examples),'independent_observations':[
   {'status':'CONFIRMED','fact':'Both near and far function returns occur. Near/far alone does not distinguish cdecl from Pascal.'},
   {'status':'CONFIRMED','fact':'RallocType/Size/SetType consume 4-byte pointers using LES; RallocFreed tests both words of a stored pointer.'},
   {'status':'CONFIRMED','fact':'RandTurn has a near return and a far call to SRand8, then reads TurnTab through a DGROUP selector pool slot relocated to segment 8.'},
   {'status':'CONFIRMED','fact':'win_SetWinDrawHook stores a four-byte value at array stride four in segment 9; the function-pointer interpretation follows its name and consumers.'},
   {'status':'CONFIRMED','fact':'WindowsMemCpy increments pointer offsets and uses KERNEL ordinal 114 (__AHINCR per SDK LIBW) on carry: huge-pointer arithmetic.'},
   {'status':'STRONGLY SUPPORTED','fact':'Large-model defaults plus explicit near functions/data and explicit huge pointers. Medium defaults with explicit far data remain observationally possible.'},
   {'status':'POSSIBLE','fact':'Near routines may be source near/static declarations or compiler-local decisions; SYM lacks original translation-unit boundaries.'}]
 }
 write_json(ROOT/'evidence/experiments/toolchain/memory-model.json',evidence)
 for x in out:print(x['name'],x['counts'])

if __name__=='__main__':main()
