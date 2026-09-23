# Isolated local-order replay for `_GetEnterDirB` / `_GetEnterDirR`

## Question and starting evidence

Both jobs belong to assigned component `simone:12E4`, compiled with MSC 7.00
`/AL /G2 /Gs /Oelw /NTSIMONE_MODULE`. Their preserved attempt 02 sources match
all 60 opcodes and 12 fixups, with 127/132 ordinary bytes. The same five local
slot differences occur in both functions:

| Offset | Target stack operand | Candidate stack operand |
| --- | --- | --- |
| `0x0B` | `[bp-4]` | `[bp-6]` |
| `0x27` | `[bp-6]` | `[bp-4]` |
| `0x2C` | `[bp-4]` | `[bp-6]` |
| `0x75` | `[bp-6]` | `[bp-4]` |
| `0x85` | `[bp-6]` | `[bp-4]` |

The candidates store `dir ^ 4` and the initial best map value into the opposite
scratch slots from the target, then carry that swap into the loop. Attempts
02–07 for B and 02–07 for R had already repeated this same compiler result.

## Isolated tests

First, each preserved source was compiled alone with the current declarations
and with only `back` and `bestValue` declarations exchanged. Both two-candidate
batches collapsed to one object hash per function. The swapped declaration
order changed no bytes and retained all five stack differences.

Then, both source bodies were composed into one research-only TU matching the
known two-public component context. A four-candidate cross-product tested the
baseline and swapped declaration orders independently for B and R. All four
sources collapsed to one object hash (`630a0fa2…c45868f`). Evaluating B and R
against that combined object retained the same local slot differences. The
strict member comparison also reported unresolved private CONST placement and
unmatched member fixups because this experiment did not reconstruct the full
object context; it is diagnostic evidence only.

## Result and next level

The direct `back`/`bestValue` declaration permutation does not control these
stack homes under the assigned standalone profile or when both functions are
compiled together. This is negative evidence scoped to the tested source form
and context. It does not establish a general MSC7 rule or justify reopening
either escalated production job.

The next discriminating research should trace why the optimizer assigns the
two scalar homes in the opposite order, including function-local use/lifetime
shape and the exact same-object declaration/compiler context. Further simple
permutations of these two declarations are not justified by the observed
output collapse.

## Receipts

- Standalone B: [`spec.json`](spec.json), [`receipt.json`](receipt.json),
  [`out/results.json`](out/results.json)
- Standalone R: [R spec](../../../GetEnterDirR-4cef7555bd/isolated-research/local-declaration-order/spec.json),
  [R receipt](../../../GetEnterDirR-4cef7555bd/isolated-research/local-declaration-order/receipt.json),
  [R results](../../../GetEnterDirR-4cef7555bd/isolated-research/local-declaration-order/out/results.json)
- Same-TU B/R local-order cross-product: [`template.c`](../same-tu-locals/template.c),
  [`spec-B.json`](../same-tu-locals/spec-B.json), [`report-B.json`](../same-tu-locals/report-B.json),
  [`spec-R.json`](../same-tu-locals/spec-R.json), [`report-R.json`](../same-tu-locals/report-R.json)

No production attempts, job states, manifests, recipes, or compiler tools were
changed by these experiments.
