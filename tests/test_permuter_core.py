import random
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import c_source
import permuter
import permuter_mutations as M


def test_dialect_keyword_adapter_round_trips_msc_words():
    sample = ('far near __far __based(__segname("PACK")) __segment pascal cdecl '
              'huge _based register volatile')
    assert M.dialect_roundtrip(sample) == sample
    assert 'volatile' in M.map_dialect('void F(){ volatile int x; }')
    assert 'volatile' in M.map_dialect('void F(){ int far *p; }')


def test_far_and_real_volatile_render_as_distinct_source_keywords():
    source = 'void F(){ volatile int marker; int far *p; p = (int far *)0; }'
    codec = M.BodyCodec(source, 'F')
    rendered = codec.render(codec.body)
    assert 'volatile int marker' in rendered
    assert 'int far *p' in rendered
    assert '(int far *)' in rendered


def test_based_segment_and_string_contents_survive_dialect_mapping():
    source = 'void F(){ char __based(__segname("PACK")) *p; p = 0; }'
    codec = M.BodyCodec(source, 'F')
    rendered = codec.render(codec.body)
    assert '__based(__segname("PACK"))' in rendered
    quoted = 'void F(){ char *s = "far __based"; }'
    assert M.map_dialect(quoted) == quoted


def test_calling_convention_words_in_body_are_restored_after_ast_render():
    source = 'void F(){ int (pascal *cb)(int); int (cdecl *other)(int); }'
    codec = M.BodyCodec(source, 'F')
    rendered = codec.render(codec.body)
    assert 'pascal *cb' in rendered
    assert 'cdecl *other' in rendered


def test_body_splice_leaves_signature_and_rest_of_tu_verbatim():
    source = 'int before;\nvoid F(){ int x; x=1; }\nvoid Other(){ int y; y=2; }\n'
    codec = M.BodyCodec(source, 'F')
    output = codec.splice(codec.render(codec.body))
    start, end = codec.loc['body_start'], codec.loc['body_end']
    assert output[:start] == source[:start]
    assert output[-(len(source) - end):] == source[end:]


def test_statement_swap_rejects_read_write_dependency_and_memory_aliasing():
    dependent = M.BodyCodec('void F(){ a=1; a=a+1; }', 'F').body
    assert M.m_stmt_swap(dependent, random.Random(0)) is None
    memory = M.BodyCodec('void F(){ *p=1; x=*p; }', 'F').body
    assert M.m_stmt_swap(memory, random.Random(0)) is None


def test_statement_swap_allows_independent_scalar_assignments():
    independent = M.BodyCodec('void F(){ a=1; b=2; }', 'F').body
    assert M.m_stmt_swap(independent, random.Random(0)).startswith('stmt_swap:')


def test_known_msc_noop_spellings_are_not_mutated():
    addition = M.BodyCodec('void F(){ x = a + b; }', 'F').body
    assert M.m_swap_commutative(addition, random.Random(0)) is None
    scaled = M.BodyCodec('void F(){ x = p[i*8+j]; }', 'F').body
    assert M.m_index_pointer(scaled, random.Random(0)) is None


def test_chain_assignment_guard_rejects_same_or_volatile_objects():
    same = M.BodyCodec('void F(){ a=0; a=0; }', 'F').body
    assert M.m_chain_assign(same, random.Random(0)) is None
    volatile = M.BodyCodec('void F(){ volatile int a; volatile int b; a=0; b=0; }', 'F').body
    assert M.m_chain_assign(volatile, random.Random(0)) is None


def test_dedupe_distinguishes_source_from_fixup_masked_output_identity():
    index = permuter.DedupeIndex()
    assert index.add_source('a=1;')
    assert not index.add_source('a=1;')
    assert index.add_source('a=2;')
    assert index.add_output('masked-member-hash')
    assert not index.add_output('masked-member-hash')


def test_cost_orders_exact_then_frame_then_earlier_divergence_cost():
    exact = permuter.score({'result': 'CONFIRMED_MEMBER', 'diagnostic': {
        'exact_match': True, 'opcode_matches': 2, 'opcode_total': 2,
        'aligned_asm': [{'target': 'enter 2, 0', 'candidate': 'enter 2, 0', 'differences': []}]}})
    wrong_frame = permuter.score({'result': 'NO_COMPLETE_MATCH', 'diagnostic': {
        'exact_match': False, 'opcode_matches': 1, 'opcode_total': 2,
        'aligned_asm': [{'target': 'enter 2, 0', 'candidate': 'enter 4, 0',
                         'differences': ['instruction_shape']}]}})
    late_better = permuter.score({'result': 'NO_COMPLETE_MATCH', 'diagnostic': {
        'exact_match': False, 'opcode_matches': 8, 'opcode_total': 10,
        'aligned_asm': [
            {'target': 'mov ax, bx', 'candidate': 'mov ax, bx', 'differences': []},
            {'target': 'add ax, 1', 'candidate': 'add ax, 2', 'differences': ['immediate_or_binding']}],}})
    assert permuter.rank(exact) > permuter.rank(wrong_frame)
    assert wrong_frame['frame_equal'] is False
    assert late_better['first_divergence_row'] == 1
    assert late_better['aligned_cost'] < 1


def test_resolved_fixup_operand_noise_does_not_add_aligned_cost():
    value = permuter.score({'result': 'NO_COMPLETE_MATCH', 'diagnostic': {
        'exact_match': False, 'opcode_matches': 1, 'opcode_total': 1,
        'aligned_asm': [{'target': 'mov ax, resolved fixup selector',
                         'candidate': 'mov ax, resolved fixup selector+2',
                         'differences': ['immediate_or_binding']}]}})
    assert value['aligned_cost'] == 0
    assert value['first_divergence_row'] == 2
