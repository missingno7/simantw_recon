"""Conservative binding-only routing; never an admission or semantic oracle."""


def classify(comparison):
    d = comparison.get('diagnostic', {})
    if comparison.get('result') != 'NO_COMPLETE_MATCH':
        return None
    if not (d.get('instruction_layout_match') is True and
            d.get('cfg_shape_match') is True and d.get('extent_known') is True and
            d.get('target_bytes') == d.get('candidate_bytes') and
            d.get('opcode_matches', 0) == d.get('opcode_total', -1) and
            d.get('first_structural_difference') is None):
        return None
    if any(d.get(k, 1) != 0 for k in ('register_only_differences',
            'branch_target_differences', 'stack_local_differences')):
        return None
    # A score/category alone is insufficient: every differing literal byte in
    # the complete contribution must be covered by a failing offset binding.
    failures = []
    for c in comparison.get('contributions', []):
        allowed = set()
        for f in c.get('fixups', []):
            if f['equal']:
                continue
            o = f['omf']
            if o['location_type'] != 1 or o['self_relative'] or o['width'] != 2:
                return None
            if o['target'].get('kind') not in ('external', 'segment'):
                return None
            # The matcher resolved the target but the literal disagreed: that is
            # a wrong index/displacement in the source, not an unresolved binding.
            if f.get('target') is not None and f.get('reason') in ('resolved offset and frame', 'same-segment relative offset'):
                return None
            allowed.update(range(f['offset'], f['offset'] + 2))
            failures.append(dict(contribution=c['segment'], offset=f['offset'],
                                 target=o['target'], reason=f['reason']))
        # Matcher truncates divergence lists at 512: do not infer coverage then.
        differences = c.get('literal_compared', 0) - c.get('literal_equal', 0)
        if differences != len(c.get('divergences', [])):
            return None
        if not set(c.get('divergences', [])).issubset(allowed):
            return None
    if not failures:
        return None
    changed = [r for r in d.get('aligned_asm', []) if r['differences']]
    if not changed or any(set(r['differences']) - {'memory_operand', 'immediate_or_binding'}
                          or r['target'].split()[0] in ('call', 'lcall', 'jmp', 'ljmp')
                          for r in changed):
        return None
    return dict(state='BODY_MATCHED_BINDING_BLOCKED', recovery_credit=0,
                scope='Literal body and control flow agree outside unresolved offset bindings; data identity and semantics still require review',
                failed_bindings=failures,
                next_action='Preserve body; reconstruct shared declarations/contributions and retest complete members')
