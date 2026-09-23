Focused MSC 7.00 probes for the tree segment access question.

The target `_InitTree` loads ES once from `unpackHandle+2` and then performs two
`REP STOSW` runs. `_DeleteNode` and `_InsertNode` save DS, load that same selector
once, and use near offsets. These sources test whether ordinary far/based C
accesses can produce those register patterns under the unit's established flags.
They are compiler experiments, not recovery candidates or admissions.

Compiled with authentic MSC 7.00 and the established SIMTWO flags
`/AL /G2 /Gs /Oelw /NTSIMTWO_MODULE` on 2026-09-23:

| Probe | Code bytes | Observed segment access |
| --- | ---: | --- |
| `far-array.c` | 46 | `mov es,[CONST]`, then `mov ax,es:[unpackHandle+2]` |
| `based-local.c` | 36 | same indirect selector fetch, two ES setups |
| `based-near.c` | 32 | direct `mov ax,[unpackHandle+2]`, two ES setups |
| `based-direct.c` | 28 | direct `mov es,[unpackHandle+2]`, one ES setup |
| `named-fields.c` | 26 | direct selector access, two unresolved named offsets |
| `named-segment.c` | 26 | direct selector access, two unresolved named offsets |

Thus the far pointer **object** needs a near declaration to get the target's
DGROUP access. This does not prove the source declaration of the tree fields.
The `based-direct` spelling matches `_InitTree`'s 28-byte extent but differs in
instruction order and produces an internal selector fixup. Job attempt 9 is
the full member comparison. `_DeleteNode` attempt 7 applies the near object
declaration to its preserved algorithm: selector binding improves, but its
ES-relative 370-byte body remains far from the 189-byte DS-relative target.
The source-level DS switch is still unresolved.
