# PrepareStrings source recovery

The live packet showed eighteen consecutive calls to `_LoadStringAnt`, each
followed by a far pointer store. The pushed resource IDs and possible MAPSYM
owner names determined the order in `first.c`; the `PictStrnDialog` recovered
source supplied the far return type. This was one source hypothesis, not a
search over guessed object bytes.

`grind.py test` recorded `EXACT_CANDIDATE`: 433/433 target body bytes,
145/145 aligned opcodes, 90/90 semantic fixups, and no private contribution
issue. The candidate object has a separate trailing alignment byte. The
immutable CRLF-normalized candidate is under
`evidence/recovery/workflow/jobs/PrepareStrings-9dd732cc1e/attempt01/`;
the strict independent `grind.py accept` promoted that exact candidate to
`src/recovered/wf_PrepareStrings-9dd732cc1e.c`. The job's promotion proof is
the authority for recovery credit.
