# Candidate near-prototype audit

The original linked code frequently contains `NOP; PUSH CS; CALL near`. The
verified LINK 5.30 experiment shows that this is the five-byte same-segment
translation of a source far call. The `near_call` label in a card identifies the
final opcode, not necessarily the historical C declaration.

`python tools/call_abi_audit.py` scans preserved workflow `candidate.c` files
for `extern ... near Function(...)` declarations and compares named direct
call sites in the corresponding original card. It reports only cases with the
exact contiguous `90 0E E8` prefix. The report includes source hashes, job
status, call offsets and bytes so each warning is independently reviewable.
Use `--symbol _DropMyFood` for one target.

After the 2026-09-24 `_DropMyFood` far-prototype retest, 130 near-function
declarations had resolved target call sites. [The preserved report](results.json)
flags 39 declarations across 23 jobs (37 escalated, one needing revision, and
one in a stale promoted job candidate).
These are review leads, not automatic source fixes or recovery credit. The
source body, private contributions, fixups and unit context still require
strict proof. An earlier `_DropMyFood` candidate's near `IsClearTile`
declaration was one example: target sites at `SIMONE:7769` and `SIMONE:78AD`
share the same `90 0E E8` signature as admitted `_IsClear3x3` far
`IsClearTile` calls. The controlled far-prototype retest remains nonexact
(`attempt03`); it does not establish a complete body or unit context.

This audit is scoped to the current cards and current candidate files; it
does not infer declarations for unresolved or indirect calls. The established
linker behavior and independent proof remain in
`evidence/experiments/toolchain/link-probe/`.
