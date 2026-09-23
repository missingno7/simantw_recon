# `_InitApplication` trailing-local frame test

The preserved production candidate is 315 bytes, 90/90 aligned opcodes and
20/20 fixups under MSC 7.00 baseline. Its `enter 0x11e` frame and every
WNDCLASS stack home are 26 bytes shallower than the target's `enter 0x138`.
Earlier production trials tested declaration order, declaration grouping,
an unused WNDCLASS before the used locals, and a three-element array.

This isolated five-candidate batch tested the remaining placement question:
an unused WNDCLASS or 26-byte array *after* the three used locals, each with
and without `volatile`, plus an unchanged control. `run.py` creates the
bounded source template and `spec.json`; `run/` retains every source, receipt,
strict result and instruction diff. `compact.json` groups effective objects.

There were only two OMF classes. The unchanged source, trailing ordinary
WNDCLASS, and trailing ordinary 26-byte array all compiled identically with
`enter 0x11e`, 90/90 opcodes and 20/20 fixups. Both trailing `volatile`
forms compiled to one second object with a *smaller* `enter 0x104` frame,
again 90/90 opcodes and 20/20 fixups. Neither form produced the target
`enter 0x138` or resolved the 33 stack-home differences.

This closes a local declaration-placement family for this source/profile.
The next discriminating level is evidence for the original function's
translation-unit or compiler allocation context, or a different lexical
use/lifetime that reserves one 26-byte slot without adding instructions.
This batch does not reopen the production job or grant recovery credit.
