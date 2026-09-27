"""Build non-credited selector-pool prefixes for isolated search candidates."""
import re
from functools import lru_cache
from pathlib import Path

from common import ROOT, FormatError, fixture, read_json, relative

POOL_MAP_DIR = ROOT / 'evidence/experiments/pool-maps'
TOPOLOGY = ROOT / 'evidence/topology/build-topology.json'


def component_pool_prefix_words(pool_map, symbol, functions, selector_words=None):
    """Return component pool words preceding ``symbol``'s original block.

    Missing maps and members without selector slots have no prefix. Use the
    same block bounds as TU scaffolding, then keep only actual selector slots
    from the NE relocation inventory. A map can span non-selector CONST holes;
    treating those as far references would shift the candidate's pool.
    """
    if not pool_map:
        return []
    function = functions.get(symbol) or {}
    slots = [int(w, 16) if isinstance(w, str) else int(w) for w in function.get('slots', [])]
    if not slots:
        return []
    first_own = min(slots)
    listed = sorted({int(w, 16) if isinstance(w, str) else int(w)
                     for w in pool_map.get('scope', {}).get('pool_words', [])})
    if not listed or first_own <= listed[0]:
        return []
    import tu_assembly as tu
    block = tu.required_pool_block(listed, slots)
    prefix = [w for w in block if w < first_own]
    if selector_words is not None:
        return [w for w in prefix if w in selector_words]
    listed_set = set(listed)
    return [w for w in prefix if w in listed_set]


@lru_cache(maxsize=None)
def load_component_pool_map(component_id, pool_dir=POOL_MAP_DIR):
    """Load the evidence map for a topology component, or return None."""
    path = Path(pool_dir) / (component_id.replace(':', '_') + '.json')
    return read_json(path) if path.is_file() else None


@lru_cache(maxsize=1)
def _pool_environment():
    import mapsym
    import tu_assembly as tu
    return (tu, tu.topology_units(), read_json(TOPOLOGY)['functions'],
            mapsym.parse(fixture('SIMANTW.SYM')), tu.slot_segments(), tu.far_sites())


def pool_word_references(pool_map, words, slot_segments, sites, symbols, used_names=()):
    """Choose one distinct, segment-correct scaffold reference per word."""
    import tu_assembly as tu
    rows = {int(row['word'], 16): row for row in pool_map.get('words', [])}
    used, references = set(used_names), []
    unresolved = []
    for word in words:
        row = rows.get(word, dict(word='0x%04X' % word, symbol='UNRESOLVED', confidence='UNRESOLVED'))
        relocation = row.get('ne_relocation') or {}
        segment = relocation.get('target_segment_number')
        if segment is None:
            segment = slot_segments.get(word)
        if segment is None or slot_segments.get(word) != segment:
            raise FormatError('pool map relocation disagrees with the NE selector pool at %04X' % word)
        preferred = _map_symbol(row)
        references.append(tu.scaffold_pool_reference(word, segment, used, sites, symbols,
                                                     preferred_name=preferred))
        if row.get('confidence') == 'UNRESOLVED' or preferred is None:
            unresolved.append('%04X' % word)
    return references, unresolved


def _component_for_symbol(symbol, components):
    matches = [cid for cid, comp in components.items() if symbol in comp.get('publics', [])]
    if len(matches) > 1:
        raise FormatError('symbol belongs to multiple topology components: ' + symbol)
    return matches[0] if matches else None


def _map_symbol(pool_row):
    name = pool_row.get('symbol')
    return name if isinstance(name, str) and name.startswith('_') and pool_row.get('confidence') != 'UNRESOLVED' else None


def pool_prefix(symbol, candidate_source=''):
    """Return ``(source_prefix, metadata)`` or an unapplied reason.

    The prefix uses tu_assembly's shared scaffold reference selection and text
    emitter, so unresolved words each receive a distinct selector allocation
    in the reserved POOLSTUB_TEXT segment.
    """
    import tu_assembly as tu
    tu, components, functions, symbols, slot_segments, sites = _pool_environment()
    component_id = _component_for_symbol(symbol, components)
    if component_id is None:
        return '', dict(applied=False, reason='symbol has no topology component')
    pool_map = load_component_pool_map(component_id)
    if pool_map is None:
        return '', dict(applied=False, component=component_id, reason='component has no pool map')
    path = POOL_MAP_DIR / (component_id.replace(':', '_') + '.json')
    slots = tu.pool_words_in_code_order(symbol, functions)
    contiguous, pool_shape = tu.assemblable([symbol], functions)
    if not contiguous:
        return '', dict(applied=False, component=component_id, pool_map=relative(path),
                        reason='candidate selector references are not one contiguous ascending block: ' + pool_shape,
                        candidate_pool_slots=['%04X' % w for w in slots])
    own_slots = set(slots)
    listed_slots = {int(w, 16) if isinstance(w, str) else int(w)
                    for w in pool_map.get('scope', {}).get('pool_words', [])}
    if not own_slots <= listed_slots:
        return '', dict(applied=False, component=component_id, pool_map=relative(path),
                        reason='component pool map does not cover every selector word used by candidate',
                        candidate_pool_slots=['%04X' % w for w in slots])
    words = component_pool_prefix_words(pool_map, symbol, functions, slot_segments)
    if not words:
        return '', dict(applied=False, component=component_id, pool_map=relative(path), reason='no preceding selector words')

    declared_texts = {}
    if candidate_source:
        declaration_source = re.sub(r'^\s*#\s*pragma[^\n]*$', '', candidate_source,
                                    flags=re.M | re.I)
        try:
            source_items = tu.split_items(declaration_source)
        except FormatError:
            # Historical drafts may carry another unsupported directive. The
            # source checker still reports it; omit optional declaration hints
            # and let MSC diagnose any collision in the generated prefix.
            source_items = []
        for item in source_items:
            if item['kind'] == 'declaration':
                for name in item.get('names', []):
                    declared_texts.setdefault(name, item['text'])
    references, unresolved = pool_word_references(pool_map, words, slot_segments, sites, symbols,
                                                   used_names=declared_texts)

    # scaffold_text is the same emitter used by tu_assembly.build --scaffold.
    # One stand-in references words in ascending order, preserving the original
    # first-use sequence while its code is excluded by the strict matcher.
    stub_name = 'pool_prefix_' + re.sub(r'[^A-Za-z0-9_]', '_', symbol.lstrip('_'))
    plan = dict(stubs=[dict(function=stub_name, position=-1, references=references,
                            filler=True, after='search prefix')], runs=[])
    parts = tu.scaffold_text(plan, declared_texts)
    lines = parts['declarations'] + parts['prototypes'] + parts['pragmas']
    lines += [definition['text'] for definition in parts['definitions']]
    text = '\n'.join(lines) + '\n'
    return text, dict(applied=True, component=component_id, pool_map=relative(path),
                      prefix_words=['%04X' % w for w in words],
                      unresolved_words=unresolved, references=references,
                      segment=tu.SCAFFOLD_SEGMENT)


def apply_pool_prefix(symbol, source):
    prefix, metadata = pool_prefix(symbol, source)
    if not prefix:
        return source, metadata
    return prefix + '\n' + source, metadata
