# Window object error-string identity

The target `_win_ObjAddr` and `_win_SetObjBitmap` both push DGROUP BD12 for
`"Attempt to get obj address outsize window"`. `_win_SetObjBitmap` also pushes
BDDA for its distinct `"Attempt to set bitmap on non-bitmap object"` message.
BD12 and BDDA are separated by other initialized strings and four `0x8000`
words in the original image.

`same-literal.c` and `same-literal-proof.json` show that MSC 7 emits two
42-byte DATA copies for two identical function-local literal expressions in
one translation unit. A shared named static in `win_ObjAddr-named.c` retains
that admitted member's complete 72-byte code and its 42-byte DATA contribution
at BD12 under both its baseline flags and `/GA` (`named-trial/` and
`named-ga-trial/`).

`win_SetObjBitmap-shared.c` references that name externally and retains its
second literal. `shared-trial/` has the target's 124-byte instruction layout,
46/46 opcodes, an exact 43-byte DATA contribution at BDDA, and one unresolved
external binding at code offset 0x2F for BD12; all other fixups agree. This is
a contextual source hypothesis, not an admission. The current isolated
`_win_ObjAddr` recipe still uses a literal and cannot be composed with the
external reference as two independent admitted objects. A complete unit must
establish the shared static's ownership and the intervening DATA declarations
without duplicate contributions or copied filler bytes.
