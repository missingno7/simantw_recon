"""Verify built recovery artifacts separately from construction."""
from common import ROOT,read_json,write_json,fixture,identity,FormatError
from compiler import validate_receipt
from matcher import compare
from recovery_gate import check_member
from library_match import compare_member,import_symbols
import omf,ne,mapsym

def verify(manifest=None,recipes=None,publish=True):
    if manifest is None:manifest=read_json(ROOT/'build/recovered/manifest.json')
    if recipes is None:recipes=read_json(ROOT/'src/recovery.json')['targets']
    if len(manifest['game_objects'])!=len(recipes):raise FormatError('duplicate or incomplete game manifest')
    raw=fixture('SIMANTW.EXE');n=ne.parse(raw);s=mapsym.parse(fixture('SIMANTW.SYM'))
    imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB');game=[];runtime=[];validated_locks=set()
    good={'FUNCTION_MATCH','CONFIRMED_MEMBER','STRONGLY_SUPPORTED_MEMBER'}
    for row in manifest['game_objects']:
        if identity(ROOT/row['object'])!=row['identity']:raise FormatError('changed built object')
        validate_receipt(row['receipt'],validated_locks);target=recipes[row['symbol']]
        if row['identity']!=row['receipt']['object_identity']:raise FormatError('object differs from compile receipt')
        if row['receipt']['source']!=target['source'] or row['receipt']['flags']!=target['flags'] or row['receipt']['compiler']!=target['compiler']:raise FormatError('stale build recipe')
        m=omf.parse((ROOT/row['object']).read_bytes())
        if target['comparison']=='data_member':
            from recovery_gate import check_data_member
            result=check_data_member(m,raw,n,s,imports,{k:v for k,v in recipes.items() if v['source']==target['source']})
        else:result=check_member(m,raw,n,s,imports,{row['symbol']:target},scaffold=bool(target.get('scaffold'))) if target['comparison']=='member' else compare(m,raw,n,s,dict(target,symbol=row['symbol']))
        if not result or result['result'] not in good:raise FormatError('recovery mismatch '+row['symbol'])
        game.append(dict(symbol=row['symbol'],source=target['source'],object=row['object'],receipt=row['receipt'],comparison=result,size=target['size']))
    ledger=read_json(ROOT/'layout/runtime-ownership.json')
    if len(manifest['runtime_objects'])!=len(ledger['members']):raise FormatError('incomplete runtime build')
    for row,member in zip(manifest['runtime_objects'],ledger['members']):
        if identity(ROOT/row['object'])!=row['identity'] or row['identity']['sha256']!=member['member_sha256']:raise FormatError('changed runtime member')
        result=compare_member(omf.parse((ROOT/row['object']).read_bytes()),raw,n,s,imports)
        if not result or result['result'] not in good:raise FormatError('runtime mismatch '+row['member'])
        runtime.append(dict(member=row['member'],object=row['object'],identity=row['identity'],comparison=result))
    if set(row['symbol'] for row in game)!=set(recipes):raise FormatError('incomplete game build')
    code=[r for r in game if recipes[r['symbol']].get('kind')!='DATA'];data=[r for r in game if recipes[r['symbol']].get('kind')=='DATA']
    report=dict(phase='MATCHED_OBJECT_RECOVERY',game_functions=len(code),game_code_bytes=sum(r['size'] for r in code),game_data_symbols=len(data),game_data_bytes=sum(r['size'] for r in data),
                runtime_members=len(runtime),runtime_code_bytes=ledger['unique_code_bytes'],whole_executable_build=False,game=game,runtime=runtime)
    if publish:
        # The detailed report is derived output; only the compact totals are versioned.
        write_json(ROOT/'build/recovery/verified-objects.json',report)
        write_json(ROOT/'docs/progress.json',{k:v for k,v in report.items() if k not in ('game','runtime')})
        print('Verified',report['game_functions'],'recovered game functions,',report['game_data_symbols'],'data symbols and',len(runtime),'complete historical runtime members')
    return report

def main():return verify()

if __name__=='__main__':main()
