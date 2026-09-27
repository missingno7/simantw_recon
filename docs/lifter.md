# MSC 7 Win16 first-draft lifter

`python tools/lift.py SYMBOL --out DIR` writes a readable C hypothesis from the
inspection packet. `--open` visits open GAME functions, `--controls` selects
admitted C functions, `--limit N` bounds either set, and `--refine` lets
`search.py` compare bounded commutative-expression and local-declaration-order
variants. The output is a draft only: recovery credit still requires the normal
whole-member proof through `search.py` and `promote.py`.

## Rules verified so far

- The packet provides the target extent, code bytes, decoded operands, loader
  bindings, MAPSYM names, references, profile, and unit context. Branch and
  memory offsets are interpreted relative to the function or segment as the
  packet records them. Relocation-chain words are never emitted as source
  constants.
- The four fixed controls `_CountUpdate`, `_IsItWall`, `_ClosePalette`, and
  `_ProcMenuHelp` produce strict members. Across them, far calls, a signed
  conditional, a named DGROUP object, and an imported far Pascal call with a
  far string and long argument each have an exact observed example. These
  examples do not establish a universal register-allocation or call-argument
  rule.
- The frame reader recognizes `push bp; mov bp,sp`, `enter N,0`, saved SI/DI,
  and the `inc bp; push ds` exported far shell. BP-relative observations use
  `frame_map.target_frame`; control measurements show that this frame prior is
  not enough to predict MSC 7's complete local layout or SI/DI allocation.
- Standalone declarations can be assembled from packet references and
  declaration-only material in admitted sources. Struct tags are indexed
  separately from function bodies so pointer prototypes and aggregate-backed
  global accesses can compile in a standalone draft. Conflicting same-name
  layouts across source files are not yet reconciled by unit identity.
- An exact MAPSYM scalar address is emitted as `&name`; array declarations use
  `&name[0]`. A struct-backed global is read through a width-appropriate
  pointer at the observed byte offset. These rules fix compile failures in the
  stratified sample but do not prove all selector or private-data bindings.
- Only reviewed HIGH/MEDIUM selector-pool rows are used to name far data.
  Unresolved selectors and private contributions remain explicit residues for
  the search proof to expose.
- Conditional signedness follows the nearby signed or unsigned condition
  branch where available. The structurer folds single-entry if-skips and simple
  back-edge loops; shared tails and uncertain regions retain labels and gotos.
- `adc` and `sbb` now use explicit masked carry/borrow temporaries, with nearby
  `cmp`, `test`, `add`, and `sub` updating the carry state when the function has
  a carry-chain instruction. This compiles on `_DeleteIndex`, but opcode
  agreement fell from 43/97 to 40/97 there, so this statement form is not a
  proven MSC source idiom yet.

## Current measured limit

On the first 52-function stratified control sample, the declaration/address
iteration compiles 40/52 drafts (76.9%), matches 8/52 strictly (15.4%), and has
72.9% median opcode agreement among compilable drafts. Expression shape, memory
operands, immediate/fixup binding, branch targets, alignment, register choice,
far-call stack binding, and frame layout remain common mismatch classes. See
`build/workers/f-infra-lift/REPORT.md` for iterations and the open-function
measurement. The complete 405-function open pass compiled 281 drafts; 260
reached 90% of target bytes, none were strict, and none beat the existing best.
Across all 678 admitted C controls, 527 drafts compiled, 101 were strict, and
median opcode agreement among compilable controls was 64.1%.
