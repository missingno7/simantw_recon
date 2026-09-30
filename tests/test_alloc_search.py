import copy
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import alloc_search as A
import permuter_mutations as M


def row(target, candidate, differences=()):
    return dict(target_offset=0, target=target, candidate_offset=0, candidate=candidate,
                differences=list(differences))


def test_location_tokens_split_registers_homes_and_index_registers():
    assert A.location_tokens('mov word ptr [bp - 0xa], ax') == [('home', -10), ('reg', 'ax')]
    assert A.location_tokens('les si, ptr [bp + 6]') == [('reg', 'si'), ('home', 6)]
    assert A.location_tokens('mov al, byte ptr es:[bx + si + 4]') == [('reg', 'al'), ('reg', 'es'),
                                                                     ('reg', 'bx'), ('reg', 'si')]
    assert A.location_tokens('mov ax, word ptr [bp + di - 4]') == [('reg', 'ax'), ('home', -4), ('reg', 'di')]
    assert A.location_tokens('ret') == []


def test_objective_moves_when_one_home_or_register_flips():
    exact = [row('mov word ptr [bp - 2], si', 'mov word ptr [bp - 2], si'),
             row('push di', 'push di')]
    flipped_home = [row('mov word ptr [bp - 2], si', 'mov word ptr [bp - 4], si', ['memory_operand']),
                    row('push di', 'push di')]
    flipped_reg = [row('mov word ptr [bp - 2], si', 'mov word ptr [bp - 2], di', ['register_allocation']),
                   row('push di', 'push si', ['register_allocation'])]
    a, b, c = (A.allocation_objective(x) for x in (exact, flipped_home, flipped_reg))
    assert a['bad'] == 0 and a['home_ok'] == 1 and a['reg_ok'] == 2
    assert b['home_bad'] == 1 and b['reg_bad'] == 0
    assert dict(b['pairs']) == {('[bp-4]', '[bp-2]'): 1}
    assert c['reg_bad'] == 2 and dict(c['pairs']) == {('di', 'si'): 1, ('si', 'di'): 1}


def test_objective_ignores_shape_rows_and_fixup_renderings():
    rows = [row('mov ax, word ptr [bp - 2]', '', ['instruction_shape']),
            row('mov es, word ptr [0xbf90]', "mov <resolved fixup> [{'kind': 'segment'}]", ['memory_operand'])]
    rows[0]['candidate_offset'] = None
    assert A.allocation_objective(rows)['bad'] == 0


def test_rank_orders_exactness_then_opcodes_then_allocation():
    base = dict(strict=False, body_exact=False, opcode_matches=10, opcode_total=12, bad=5, pair_kinds=2,
                candidate_bytes=30, target_bytes=30)
    fewer_bad = dict(base, bad=1)
    more_opcodes = dict(base, opcode_matches=11, bad=9)
    body = dict(base, body_exact=True, bad=0, opcode_matches=10)
    assert A.rank(fewer_bad) > A.rank(base)
    assert A.rank(more_opcodes) > A.rank(fewer_bad)
    assert A.rank(body) > A.rank(more_opcodes)
    assert A.rank(dict(failed='x')) < A.rank(base)


def _codec(body_text, prelude=''):
    return M.BodyCodec(prelude + 'void F(void)\n' + body_text, 'F')


def test_enumeration_visits_every_site_of_a_mutation():
    codec = _codec('{\n    int a;\n    int b;\n    int c;\n    a = 1; b = 2; c = a + b; g = c;\n}\n',
                   'int g;\n')
    found = [d for _w, d in A.enumerate_mutation(codec.body, M.m_decl_order)]
    assert len(found) == 2          # (a,b) and (b,c)
    moves = {d for _w, d in A.enumerate_mutation(codec.body, A.m_decl_move)}
    assert len(moves) >= 4


def test_decl_move_keeps_initialiser_dependencies():
    codec = _codec('{\n    int a = 1;\n    int b = a;\n    g = a + b;\n}\n', 'int g;\n')
    for work, _d in A.enumerate_mutation(codec.body, A.m_decl_move):
        names = [x.name for x in work.block_items if x.__class__.__name__ == 'Decl']
        assert names.index('a') < names.index('b')


def test_inline_local_handles_label_and_refuses_unsafe_cases():
    prelude = 'int g; int h; int t; void f(void);\n'
    codec = _codec('{\n    int x;\n    if (h) goto done;\n    h = 1;\ndone:\n    x = g;\n'
                   '    if (x != h) t = 1;\n    h = x;\n}\n', prelude)
    work = copy.deepcopy(codec.body)
    assert A.inline_local(work, 'x')
    text = codec.render(work)
    assert 'done:' in text and 'int x' not in text and text.count('g') >= 2
    # a call between definition and use may change the global the expression reads
    codec = _codec('{\n    int x;\n    x = g;\n    f();\n    h = x;\n}\n', prelude)
    assert A.inline_local(copy.deepcopy(codec.body), 'x') is None
    # the variable's inputs are written in between
    codec = _codec('{\n    int x;\n    x = g;\n    g = 2;\n    h = x;\n}\n', prelude)
    assert A.inline_local(copy.deepcopy(codec.body), 'x') is None
    # address taken
    codec = _codec('{\n    int x;\n    int *p;\n    x = g;\n    p = &x;\n    h = *p;\n}\n', prelude)
    assert A.inline_local(copy.deepcopy(codec.body), 'x') is None


def test_strip_volatile_cast_and_follow_up_inline():
    source = ('int g; int h; int t;\nvoid F(void)\n{\n    int x;\n    x = g;\n'
              '    if (x != h) t = 1;\n    h = *(volatile int *)&x;\n}\n')
    hood = A.Neighbourhood(source, 'F')
    kids = {d: text for text, d in hood.children('strip_volatile_cast')}
    assert any(d.endswith('(1 casts)') for d in kids)
    inlined = [text for d, text in kids.items() if 'inline_local' in d]
    assert inlined and 'volatile' not in inlined[0] and 'int x' not in inlined[0]


def test_unvolatile_decl_only_touches_spelled_volatile_locals():
    source = ('int g;\nvoid F(void)\n{\n    volatile int v;\n    int far *p;\n    v = g;\n'
              '    p = 0;\n    g = v + *p;\n}\n')
    hood = A.Neighbourhood(source, 'F')
    kids = [(d, text) for text, d in hood.children('unvolatile_decl')]
    assert kids and all(d.startswith('unvolatile_decl: v') for d, _t in kids)
    assert all('int far *p' in text for _d, text in kids)


def test_volatile_names_tolerates_global_arrays_and_ignores_far_globals():
    source = ('extern int far farGlobal;\nint table[4];\nvoid F(void)\n{\n    int a;\n'
              '    a = table[1] * farGlobal;\n    table[0] = a;\n}\n')
    codec = M.BodyCodec(source, 'F')
    assert M.volatile_names(codec.body) == set()
    assert any(True for _ in A.enumerate_mutation(codec.body, M.m_swap_commutative))


def test_renderer_keeps_far_on_the_declarations_and_casts_that_spell_it():
    # Parser columns index the dialect-mapped line; a plain cast beside a far cast must not
    # gain `far`, and a pointer-level far must not become volatile (permuter_mutations fix).
    source = ('int g;\nvoid F(void)\n{\n    struct S far * far *slot;\n    unsigned char far *cell;\n'
              '    g = (int)((unsigned long)cell + 4) + (int)(void far *)cell;\n    slot = 0;\n}\n')
    codec = M.BodyCodec(source, 'F')
    text = codec.render(codec.body)
    assert 'struct S far * far *slot' in text
    assert 'unsigned char far *cell' in text
    assert '(unsigned long)' in text and 'unsigned long far' not in text
    assert '(void far *)' in text and 'volatile' not in text


def test_strip_volatile_cast_matches_the_rendered_parenthesised_form():
    source = ('int g; int h;\nvoid F(void)\n{\n    int x;\n    x = g;\n    h = *(volatile int *)&x;\n}\n')
    hood = A.Neighbourhood(source, 'F')
    rendered = A.Neighbourhood(hood.reference, 'F')
    assert '*((volatile int *) (&x))' in hood.reference.replace('\n', ' ') or 'volatile' in hood.reference
    assert any(d.startswith('strip_volatile_cast: x') for _t, d in rendered.children('strip_volatile_cast'))


def test_hoist_and_sink_move_a_pure_local_assignment_across_an_if():
    source = ('int g; int h; int k;\nvoid F(void)\n{\n    int t;\n    if (h > 0) {\n        t = g - k;\n'
              '        h = t + 1;\n        k = t;\n    }\n}\n')
    hood = A.Neighbourhood(source, 'F')
    kids = [(d, t) for t, d in hood.children('hoist_over_if')]
    assert len(kids) == 1 and 't = g - k' in kids[0][0]
    back = A.Neighbourhood(kids[0][1], 'F')
    sunk = [d for _t, d in back.children('sink_into_if')]
    assert sunk and sunk[0].startswith('sink_into_if: t = g - k')
    # a use after the if (or in the condition) blocks the move
    blocked = source.replace('        k = t;\n    }\n', '    }\n    k = t;\n')
    assert not A.Neighbourhood(blocked, 'F').children('hoist_over_if')
    # a dereference is not hoisted (it could fault on the path that skipped it)
    deref = source.replace('t = g - k;', 't = *(int *)g;')
    assert not A.Neighbourhood(deref, 'F').children('hoist_over_if')


def test_split_aggregate_turns_member_only_struct_into_scalars():
    source = ('struct Pair { int lo; int far *hi; };\nint g; int far *h;\n'
              'void F(void)\n{\n    struct Pair p;\n    struct { int a; int b; } q;\n'
              '    p.lo = g;\n    p.hi = h;\n    q.a = p.lo + 1;\n    g = q.a + *p.hi;\n}\n')
    variants = dict((d, t) for t, d in A.split_aggregate_variants(source, 'F'))
    assert set(variants) == {'split_aggregate: p -> hi, lo', 'split_aggregate: q -> a'}
    text = variants['split_aggregate: p -> hi, lo']
    assert '    int lo;' in text and '    int far *hi;' in text and 'p.' not in text
    assert 'int b' not in variants['split_aggregate: q -> a'].split('void F')[1]  # unused member dropped
    # a struct used as a whole (address taken, assigned) is left alone
    whole = source.replace('    g = q.a + *p.hi;\n', '    g = q.a + *p.hi;\n    Use(&p);\n')
    assert [d for _t, d in A.split_aggregate_variants(whole, 'F')] == ['split_aggregate: q -> a']


def test_split_web_renames_a_later_top_level_web_only():
    source = ('int g; int h;\nvoid F(void)\n{\n    int v;\n    if (g) {\n        v = g + 1;\n        h = v;\n    }\n'
              '    v = h * 2;\n    g = v;\n}\n')
    kids = [(d, t) for t, d in A.Neighbourhood(source, 'F').children('split_web')]
    assert len(kids) == 1 and kids[0][0].startswith('split_web: v from statement')
    body = kids[0][1].split('void F')[1]
    assert 'h = v;' in body and 'g = perm_v_2;' in body and 'perm_v_2 = h * 2;' in body
    # labels/gotos make the rename unsafe
    goto = source.replace('    if (g) {', '    if (h) goto out;\n    if (g) {').replace('    g = v;\n}', '    g = v;\nout:\n    h = 0;\n}')
    assert not A.Neighbourhood(goto, 'F').children('split_web')


def test_inline_temp_variants_do_not_move_global_reads_across_calls_or_stores():
    source = ('int g; int h; void f(void);\nvoid F(int *p)\n{\n    int t;\n    t = g;\n    f();\n    h = t;\n}\n')
    codec = M.BodyCodec(source, 'F')
    assert not list(A.enumerate_mutation(codec.body, M.m_inline_temp_multi))
    store = source.replace('    f();\n', '    *p = 1;\n')
    codec = M.BodyCodec(store, 'F')
    assert not list(A.enumerate_mutation(codec.body, M.m_inline_temp_multi))
    local = source.replace('    t = g;\n', '    t = 3;\n')
    codec = M.BodyCodec(local, 'F')
    assert list(A.enumerate_mutation(codec.body, M.m_inline_temp_multi))
    nxt = ('int g; int h; int f(void);\nvoid F(void)\n{\n    int t;\n    t = g;\n    h = f() + t;\n}\n')
    codec = M.BodyCodec(nxt, 'F')
    assert not list(A.enumerate_mutation(codec.body, M.m_inline_temp))


def test_array_names_are_addresses_not_shared_state():
    source = ('int g; unsigned char Map[64]; void f(void);\nvoid F(int row)\n{\n    unsigned char *cell;\n'
              '    cell = Map + row;\n    f();\n    *cell = 1;\n}\n')
    codec = M.BodyCodec(source, 'F')
    assert list(A.enumerate_mutation(codec.body, M.m_inline_temp_multi))


def test_frame_size_counts_as_a_home_operand():
    rows = [row('enter 2, 0', 'enter 8, 0', ['immediate_or_binding'])]
    objective = A.allocation_objective(rows)
    assert objective['home_bad'] == 1 and dict(objective['pairs']) == {('frame 8', 'frame 2'): 1}
    assert A.allocation_objective([row('enter 2, 0', 'enter 2, 0')])['bad'] == 0
