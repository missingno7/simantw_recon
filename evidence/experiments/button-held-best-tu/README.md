# ButtonHeld attempt 08 in the gr:4A2C unit

The previous two-member `gr_4A2C` research unit used `_ButtonHeld` attempt 01
beside admitted `_ButtonHeldInit`. That trial cannot rule out the better
attempt 08 body in the same context. `build_source.py` composed the admitted
source and the preserved attempt 08 source without changing either. The
reviewed research unit is
`evidence/recovery/units/gr_4A2C_ButtonHeldInit_2_reviewed/`; its source,
profile, source identities, compiler receipt, object and strict comparison are
recorded there.

The attempt 08 unit still returned `NO_COMPLETE_MATCH` under the assigned
baseline MSC 7 profile. Its GR_MODULE contribution is 472 bytes, with 36/460
ordinary bytes and 5/47 fixups equal; the private CONST placement constraints
conflict. The earlier attempt 01 unit was 478 bytes, 55/466 ordinary bytes and
5/48 fixups equal. The admitted initializer's leading instructions remain
aligned, but the combined `_ButtonHeld` body is still substantially different.

This rules out simply substituting the best preserved body into the existing
two-public unit as a fix. It does **not** prove that TU context is irrelevant:
the tested body is not code-exact, and unaligned later fixups cannot by
themselves establish a selector-pool mismatch. Further work needs an
evidence-backed source or representation change that aligns `_ButtonHeld`
before interpreting its selector relocation residue. No production job was
reopened and no recovery credit was added.
