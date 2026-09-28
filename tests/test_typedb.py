import json
import sys
from pathlib import Path

from pycparser import CParser, c_ast

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import c_source
import typedb


def test_parses_msc_dialect_globals_and_prototypes():
    source = '''
extern unsigned long far GameTime;
extern int __based(__segname("PACK")) *Packed;
struct Point { int x; int y; };
extern struct Point far *CurrentPoint;
typedef void (far pascal *Proc)(char far *value);
extern int far TryMoveDirB(int x, int y, int dir);
'''
    parsed = typedb._parse_unit(source)
    assert parsed['error'] is None
    names = [typedb._decl_name(ext) for ext in parsed['ast'].ext]
    assert names == ['GameTime', 'Packed', None, 'CurrentPoint', 'Proc', 'TryMoveDirB']
    game_time = typedb._decl_signature(parsed, 0, parsed['ast'].ext[0])
    assert 'unsigned long' in game_time and 'volatile' in game_time
    packed = parsed['ast'].ext[1]
    assert isinstance(packed.type, c_ast.PtrDecl)
    dependencies = typedb._dependencies_for(parsed, parsed['ast'].ext[3])
    assert any(item['name'] == 'Point' and 'struct Point' in item['declaration'] for item in dependencies)
    proc = parsed['ast'].ext[4]
    assert isinstance(proc, c_ast.Typedef)
    try_move = typedb._decl_signature(parsed, 5, parsed['ast'].ext[5])
    assert 'TryMoveDirB' in try_move and '(int,int,int)' in try_move


def test_majority_consensus_and_conflict_rows():
    forms = [
        {'signature': 'unsigned long GameTime', 'source_count': 3},
        {'signature': 'int GameTime', 'source_count': 1},
    ]
    assert typedb._choose_canonical(forms)['signature'] == 'unsigned long GameTime'
    assert len(forms) - 1 == 1  # the minority remains reportable as a conflict


def test_machine_sign_extension_infers_signed_char():
    evidence = {'access_widths': {'1': 2}, 'sign_extension': {'cbw': 2}, 'zero_extension': {}}
    assert typedb._machine_signed_type(evidence) == 'signed char'


def test_resync_prefers_verified_struct_view_used_by_member():
    source = '''
struct EditRect { int left; int top; int right; int bottom; };
extern struct EditRect far editTileRect;
int ReadBottom(void) { return editTileRect.bottom; }
'''
    parsed = typedb._parse_unit(source)
    assert parsed['error'] is None
    signature = typedb._decl_signature(parsed, 1, parsed['ast'].ext[1])
    record = {'canonical': {'signature': 'volatile struct MapPoint editTileRect'}, 'variants': [
        {'signature': 'volatile struct MapPoint editTileRect', 'source_count': 1,
         'declaration': 'extern struct MapPoint far editTileRect;',
         'dependencies': [{'name': 'MapPoint', 'kind': 'struct',
                           'declaration': 'struct MapPoint { int x; int y; };'}]},
        {'signature': 'volatile struct WinRect editTileRect', 'source_count': 1,
         'declaration': 'extern struct WinRect far editTileRect;',
         'dependencies': [{'name': 'WinRect', 'kind': 'struct',
                           'declaration': 'struct WinRect { int left; int top; int right; int bottom; };'}]},
    ]}
    chosen = typedb._resync_form(record, signature, parsed, 'editTileRect')
    assert chosen['signature'] == 'volatile struct WinRect editTileRect'


def test_resync_keeps_indexed_array_view_when_only_scalar_is_verified():
    source = '''
extern int near tileHeight[5];
int ReadHeight(void) { return tileHeight[0]; }
'''
    parsed = typedb._parse_unit(source)
    assert parsed['error'] is None
    signature = typedb._decl_signature(parsed, 0, parsed['ast'].ext[0])
    record = {'canonical': {'signature': 'volatile int tileHeight'}, 'variants': [
        {'signature': 'volatile int tileHeight', 'source_count': 4,
         'declaration': 'extern int near tileHeight;'}]}
    chosen = typedb._resync_form(record, signature, parsed, 'tileHeight')
    assert chosen['signature'] == signature


def test_resync_keeps_assignable_scalar_view_when_verified_form_is_array():
    source = '''
extern int far editBufInvalidFlag;
void ClearFlag(void) { editBufInvalidFlag = 0; }
'''
    parsed = typedb._parse_unit(source)
    assert parsed['error'] is None
    signature = typedb._decl_signature(parsed, 0, parsed['ast'].ext[0])
    record = {'canonical': {'signature': 'volatile int editBufInvalidFlag[]',
                            'declaration': 'extern int far editBufInvalidFlag[];'},
              'variants': [{'signature': 'volatile int editBufInvalidFlag[]', 'source_count': 3,
                            'declaration': 'extern int far editBufInvalidFlag[];'}]}
    chosen = typedb._resync_form(record, signature, parsed, 'editBufInvalidFlag')
    assert chosen['signature'] == signature


def test_resync_keeps_scalar_lvalue_when_verified_form_is_struct():
    source = '''
extern int far LastEggPnt;
void ResetPoint(void) { LastEggPnt = -1; }
'''
    parsed = typedb._parse_unit(source)
    assert parsed['error'] is None
    signature = typedb._decl_signature(parsed, 0, parsed['ast'].ext[0])
    record = {'canonical': {'signature': 'volatile struct MapPoint LastEggPnt',
                            'declaration': 'extern struct MapPoint far LastEggPnt;'},
              'variants': [{'signature': 'volatile struct MapPoint LastEggPnt', 'source_count': 1,
                            'declaration': 'extern struct MapPoint far LastEggPnt;',
                            'dependencies': [{'name': 'MapPoint', 'kind': 'struct',
                                              'declaration': 'struct MapPoint { int x; int y; };'}]}]}
    chosen = typedb._resync_form(record, signature, parsed, 'LastEggPnt')
    assert chosen['signature'] == signature


def test_multiline_canonical_initializer_is_replaced_once():
    candidate = 'static char near privateDGROUP[4] = "draft";'
    canonical = '''static struct PrivateData near privateDGROUP = {
    1,
    2
};'''
    rendered = typedb._replace_declaration_text(candidate, canonical, ['static'])
    assert rendered.count('=') == 1
    assert '{\n    1,\n    2\n}' in rendered


def test_resync_changes_declaration_and_preserves_function_body(tmp_path):
    source = '''extern int far GameTime;
int ReadTime(void)
{
    int local;
    local = GameTime + 1;
    return local;
}
'''
    draft = tmp_path / 'draft.c'
    output = tmp_path / 'resynced.c'
    draft.write_text(source, encoding='latin1')
    canonical = 'extern unsigned long far GameTime;'
    canonical_sig = 'volatile unsigned long GameTime'
    db = {'names': {'GameTime': {
        'canonical': {'signature': canonical_sig, 'declaration': canonical, 'sources': ['admitted.c']},
        'variants': [{'signature': canonical_sig, 'declaration': canonical, 'sources': ['admitted.c']}],
    }}, 'machine_globals': {}}

    before = c_source.find_function(source, 'ReadTime')
    before_body = source[before['body_start']:before['body_end']]
    result = typedb.resync_source(draft, output, db)
    after_source = output.read_text(encoding='latin1')
    after = c_source.find_function(after_source, 'ReadTime')

    assert result['change_count'] == 1
    assert 'extern unsigned long far GameTime;' in after_source
    assert after_source[after['body_start']:after['body_end']] == before_body


def test_resync_function_header_keeps_candidate_parameter_names(tmp_path):
    source = '''
int far Task(int supplied)
{
    return supplied + 1;
}
'''
    draft = tmp_path / 'task.c'
    output = tmp_path / 'task_resynced.c'
    draft.write_text(source, encoding='latin1')
    canonical = 'extern unsigned int far Task(unsigned int canonical_name);'
    signature = 'volatile unsigned int Task(unsigned int)'
    db = {'names': {'Task': {
        'canonical': {'signature': signature, 'declaration': canonical,
                      'dependencies': [], 'source_count': 1},
        'variants': [{'signature': signature, 'declaration': canonical,
                      'dependencies': [], 'source_count': 1, 'sources': ['admitted.c']}],
    }}, 'machine_globals': {}}
    before = c_source.find_function(source, 'Task')
    before_body = source[before['body_start']:before['body_end']]

    typedb.resync_source(draft, output, db)
    after_source = output.read_text(encoding='latin1')
    after = c_source.find_function(after_source, 'Task')

    assert 'Task(unsigned int supplied)' in after_source
    assert after_source[after['body_start']:after['body_end']] == before_body


def test_resync_does_not_drop_body_parameters_for_void_prototype(tmp_path):
    source = '''
void Draw(int flags) { if (flags) { } }
'''
    draft = tmp_path / 'draw.c'
    output = tmp_path / 'draw_resynced.c'
    draft.write_text(source, encoding='latin1')
    db = {'names': {'Draw': {
        'canonical': {'signature': 'volatile void Draw(void)', 'declaration': 'extern void Draw(void);',
                      'dependencies': []},
        'variants': [{'signature': 'volatile void Draw(void)', 'declaration': 'extern void Draw(void);',
                      'dependencies': [], 'source_count': 1, 'sources': ['admitted.c']}],
    }}, 'machine_globals': {}}
    result = typedb.resync_source(draft, output, db)
    assert result['change_count'] == 0
    assert output.read_text(encoding='latin1') == source
