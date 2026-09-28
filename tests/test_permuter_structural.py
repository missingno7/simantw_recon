import random
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import permuter_mutations as M


def _body(source, function='F'):
    return M.BodyCodec(source, function)


def _roundtrip(source, function='F'):
    codec = _body(source, function)
    rendered = codec.render(codec.body)
    again = M.BodyCodec(codec.splice(rendered), function)
    assert again.render(again.body)
    return rendered


def test_loop_interchange_requires_a_perfect_independent_two_dimensional_write_nest():
    safe = 'int map[8][8]; void F(void) { int i,j; for(i=0;i<4;i++) { for(j=0;j<4;j++) { map[i][j]=i+j; } } }'
    codec = _body(safe)
    desc = M.m_loop_interchange(codec.body, random.Random(1))
    assert desc and 'loop_interchange:' in desc
    _roundtrip(codec.splice(codec.render(codec.body)))

    one_axis = 'int map[8][8]; void F(void) { int i,j; for(i=0;i<4;i++) { for(j=0;j<4;j++) { map[i][0]=i+j; } } }'
    assert M.m_loop_interchange(_body(one_axis).body, random.Random(1)) is None
    call = 'int map[8][8]; void F(void) { int i,j; for(i=0;i<4;i++) { for(j=0;j<4;j++) { map[i][j]=G(); } } }'
    assert M.m_loop_interchange(_body(call).body, random.Random(1)) is None

    flat = ('void F(void) { unsigned char map[8192]; unsigned char *p; unsigned char value; '
            'int row,cell; for(row=0;row<256;row+=64) { for(cell=3;cell<64;cell++) {'
            'p=map+row+cell; value=*p; if(value>0) *p=value-1; } } }')
    codec = _body(flat)
    assert M.m_loop_interchange(codec.body, random.Random(1))
    _roundtrip(codec.splice(codec.render(codec.body)))

    overlapping = flat.replace('cell<64', 'cell<68')
    assert M.m_loop_interchange(_body(overlapping).body, random.Random(1)) is None

    escaped_value = flat.replace('} } }', '} } value=*p; }')
    assert M.m_loop_interchange(_body(escaped_value).body, random.Random(1)) is None


def test_split_var_needs_a_dead_old_value_and_a_later_use():
    safe = 'void F(void) { int x,a,b; x=a; x=x+1; x=b; x=x+2; }'
    codec = _body(safe)
    desc = M.m_split_var(codec.body, random.Random(3))
    assert desc and 'split_var:' in desc
    assert 'perm_x_2' in _roundtrip(codec.splice(codec.render(codec.body)))

    unsafe = 'void F(void) { int x,a,b; x=a; x=b; x=x+2; }'
    assert M.m_split_var(_body(unsafe).body, random.Random(3)) is None


def test_merge_vars_requires_equal_types_and_nonoverlapping_straight_line_ranges():
    safe = 'void F(void) { int a,b,x,y; a=x; a=a+1; b=y; b=b+1; }'
    codec = _body(safe)
    desc = M.m_merge_vars(codec.body, random.Random(2))
    assert desc and 'merge_vars:' in desc
    rendered = _roundtrip(codec.splice(codec.render(codec.body)))
    assert 'int b' not in rendered and 'b =' not in rendered

    overlap = 'void F(void) { int a,b,x,y; a=x; b=y; a=a+b; }'
    assert M.m_merge_vars(_body(overlap).body, random.Random(2)) is None


def test_call_reordering_requires_admitted_leaf_proofs_unless_risky_is_explicit():
    safe = 'int ABS(int); void CheckItem(void); void F(void) { ABS(3); CheckItem(); }'
    codec = _body(safe)
    active_types = M.TYPE_ENV
    M.admitted_pure_callees.cache_clear()
    assert 'ABS' in M.admitted_pure_callees()
    assert M.TYPE_ENV is active_types
    desc = M.m_reorder_independent_calls(codec.body, random.Random(0))
    assert desc and '(SAFE)' in desc
    _roundtrip(codec.splice(codec.render(codec.body)))

    unknown = 'void A(void); void B(void); void F(void) { A(); B(); }'
    assert M.m_reorder_independent_calls(_body(unknown).body, random.Random(0)) is None
    risky = _body(unknown)
    desc = M.m_reorder_independent_calls(risky.body, random.Random(0), allow_risky=True)
    assert desc and '(RISKY)' in desc
    _roundtrip(risky.splice(risky.render(risky.body)))


def test_hoist_invariant_requires_initialized_unsigned_inputs_and_stable_loop_body():
    safe = ('extern unsigned int input, output; '
            'void F(void) { unsigned int i; for(i=0;i<4;i++) { output=input+1; } }')
    codec = _body(safe)
    desc = M.m_hoist_invariant(codec.body, random.Random(5))
    assert desc and 'hoist_invariant:' in desc
    _roundtrip(codec.splice(codec.render(codec.body)))

    uses_index = ('extern unsigned int output; '
                  'void F(void) { unsigned int i; for(i=0;i<4;i++) { output=i+1; } }')
    assert M.m_hoist_invariant(_body(uses_index).body, random.Random(5)) is None

    uninitialized = ('extern unsigned int output; '
                     'void F(void) { unsigned int i,input; for(i=0;i<4;i++) { output=input+1; } }')
    assert M.m_hoist_invariant(_body(uninitialized).body, random.Random(5)) is None


def test_sink_invariant_needs_a_single_entry_temp_used_only_inside_loop():
    safe = ('extern unsigned int input, output; '
            'void F(void) { unsigned int i, cached; cached=input+1; '
            'for(i=0;i<4;i++) { output=cached; } }')
    codec = _body(safe)
    desc = M.m_sink_invariant(codec.body, random.Random(4))
    assert desc and 'sink_invariant:' in desc
    _roundtrip(codec.splice(codec.render(codec.body)))

    changed_input = ('extern unsigned int input, output; '
                     'void F(void) { unsigned int i, cached; cached=input+1; '
                     'for(i=0;i<4;i++) { input=input+1; output=cached; } }')
    assert M.m_sink_invariant(_body(changed_input).body, random.Random(4)) is None


def test_decl_axis_uses_only_validated_admitted_typedb_forms():
    source = ('struct MapPoint { int x; int y; };\n'
              'extern struct MapPoint far AMapPnt;\n'
              'void F(void) { }\n')
    variant, desc = M.m_decl_axis(source, random.Random(0), 'F')
    assert variant and desc and 'decl_axis: AMapPnt:' in desc
    assert 'extern int far AMapPnt[2];' in variant
    _roundtrip(variant)


def test_param_copy_roundtrips_and_refuses_address_taken_parameters():
    safe = 'int F(int p) { return p+1; }'
    codec = _body(safe)
    desc = M.m_param_copy(codec.body, random.Random(0))
    assert desc and 'param_copy:' in desc
    _roundtrip(codec.splice(codec.render(codec.body)), 'F')

    address_taken = 'int F(int p) { int *q; q=&p; return p; }'
    assert M.m_param_copy(_body(address_taken).body, random.Random(0)) is None


def test_source_axis_output_parses_as_a_complete_msc_dialect_translation_unit():
    source = ('struct MapPoint { int x; int y; };\n'
              'extern struct MapPoint far AMapPnt;\n'
              'void F(void) { }\n')
    variant, desc = M.mutate_source_axis(source, random.Random(0), only={'decl_axis'}, function='F')
    assert desc and variant != source
    import typedb
    assert typedb._parse_unit(variant, '<structural-roundtrip>')['ast'] is not None
    assert M.BodyCodec(variant, 'F').render(M.BodyCodec(variant, 'F').body)
