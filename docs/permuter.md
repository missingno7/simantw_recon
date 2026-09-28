# MSC 7.00 source permuter

`python tools/permuter.py SOURCE.c --function _Symbol` explores semantics-preserving
variants of one function body. The whole source file remains the compiler input; the
function signature, declarations, pragmas and every other function stay as supplied.
The compiler flags come from `promote.function_flags`, so each run uses the symbol's
assigned profile.

For an unnamed static helper, add its executable address and a same-object caller:

```powershell
python tools/permuter.py build/workers/me/helper.c --helper 3:63FE `
    --function DrawEditTileLeaf --like _UpdateEditIfBufInvalid `
    --time-limit 900 --iterations 100000 --batch-size 48 --beam 8 --seed 7001
```

`--function` names the non-static probe definition in the supplied translation unit;
only its body is mutated. `--like` selects the caller's assigned translation-unit
profile. Every candidate is compiled through the compiler cache and compared with
`static_probe`'s relocation-bound diagnostic after its LINK far-call translation.
Helper costs use the same ordering as symbol mode: exact body first, then frame,
earliest meaningful divergence, and aligned cost. Differences at rendered fixup
operands are excluded by the same rule as symbol mode. Exact body also requires equal
length and equal raw bytes outside bound relocation fields. A zero-cost helper result
is diagnostic evidence; the helper still has to be admitted as a `static` in its unit.

```powershell
python tools/permuter.py build/workers/me/candidate.c --function _Symbol `
    --time-limit 900 --iterations 100000 --batch-size 48 --beam 8 --seed 7001
```

Each batch is sent through `codegen_grinder.run(..., cache=True)`, which uses
`codegen_cache.compile_cached`, the authentic compiler service, the strict member matcher
and `codegen_diff.diagnose`. The ranking prefers a strict complete-member match, then an
equal frame size, then a later earliest meaningful divergence and lower aligned cost.
Operand differences rendered as resolved fixups are ignored. Output bytes are deduplicated
after masking candidate OMF fixup fields; source text is deduplicated separately.

The default mutation set includes commutation (excluding known E17 addition no-ops),
comparison mirroring, `if` inversion, De Morgan forms, loop conversions, increment/decrement
style, compound assignments, index/pointer forms (excluding E22 scaled-index no-ops),
short-circuit split/merge, ternary and `if` forms, `else` and return layouts, independent
statement swaps, single- and multiple-use temporary introduction/inlining, chained
assignment, assignment in a condition, `continue`/`else` layout, declaration sinking and
hoisting, switch-group order, and local `register` toggles. The swap guard refuses read/write
dependencies, calls, and unknown memory aliases. Width/signedness and constant-bound
rewrites require `--allow-risky`. Declaration-order and type-spelling variants are excluded
because the fact register shows they waste compiles.

The parser adapter maps MSC words such as `far`, `near`, `__far`, `huge`, `__based(...)`,
`_based(...)`, `__segment`, `__segname(...)`, `pascal` and `cdecl` for parsing and restores
them when regenerating. `register` and actual `volatile` qualifiers stay distinct; real
`volatile` is never used as a far-pointer marker.

Outputs are in `build/permuter/SYMBOL_TIMESTAMP/`: `baseline.c`, `regenerated_baseline.c`,
`best.c`, `best_min.c`, `best_min.diff`, `variants.jsonl` and `summary.json`. If the strict
member result is exact, the tool also writes `SYMBOL_exact.c` and a JSON mutation chain with
its `NATURAL` or `STEERED` classification. This result is diagnostic only. Review the
source and chain, then use the normal `search.py` and promotion gates; the permuter never
publishes a source or edits canonical state.
