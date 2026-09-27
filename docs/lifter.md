# MSC 7 Win16 symbolic lifter

`python tools/lift.py SYMBOL --out DIR` writes a readable C hypothesis from
the inspection packet. `--open` visits open GAME functions, `--controls`
selects admitted C functions, `--limit N` bounds either set, and `--refine`
searches compiler-visible variants. Lifted code is an authoring hypothesis:
only the normal complete-member proof through `search.py` and `promote.py`
earns recovery credit.

## Symbolic translation

The lifter symbolically executes the decoded function. General and segment
registers hold expression trees, while flags track the expression that sets
them. It emits C at observable boundaries: stores, calls, branches, returns,
and read-modify-write operations. This lets MSC 7.00 see the original arithmetic
and memory expressions and choose registers itself. Values kept in SI/DI across
boundaries are represented as C locals so the compiler can allocate the same
registers or homes.

Recognized source idioms include long-word `add/adc` and `sub/sbb`, compare to
boolean sequences, sign extension, far-pointer loads, selector-pool references
to named far objects, compiler runtime arithmetic helpers, `rep movsw` and
`rep stosw`, switch tables, and dense compare chains. Calls use observed stack
arguments and known declaration metadata where available. Unsupported or
ambiguous operations remain visible in the generated source and diagnostics;
the lifter does not patch object bytes or use byte directives.

Control flow is emitted as structured `if`/`else`, simple loops and `switch`
where the CFG has a safe recognizable shape. Shared tails and uncertain regions
keep labels and `goto` edges. The structured form is a source hypothesis, not
a claim that the compiler must choose the target's branches.

## Frame model and refinement

`tools/lift_frame.py` records target BP-relative homes, access widths, address
taking, use order, and loop membership. It proposes local orders and merged or
split homes, and compares `/Zi` compiler output against either an admitted
CodeView frame or the target's observed BP slots. For control measurements, the
admitted source is compiled only as a frame oracle; it is never used to produce
the lifted body.

`--refine` generates bounded alternatives for commutative operand order,
declaration order, merged homes, temporary order, and a few loop forms. It
compiles candidates with `search.py`, uses the aligned instruction prefix to
rank the first divergence, and gives exact frame coverage priority when
selecting among frame alternatives. Example:

```powershell
python tools/lift.py _SomeFunction --out build/lift2/refined --refine
```

Use `python tools/search.py SYMBOL CANDIDATE.c --frame` to inspect a candidate's
`ENTER` size and CodeView local homes. Open functions have no CodeView oracle;
their frame score checks the target's observed `ENTER` size and BP accesses.
Exact frame evidence is independent of strict body membership.

## Measured results

The v1 report records 678 admitted C controls and 405 open functions. The
current inspection cards expose 681 controls and 402 open functions (the total
remains 1,083); v2 measurements use that current split, and the worker report
records the three-symbol population shift. The report includes compile rate,
frame agreement, strict matches, opcode agreement, open-function size coverage,
and per-symbol results:

`build/workers/f-infra-lift2/REPORT.md`

Numbers are compile-loop measurements, not recovery credit. Strict matching
still checks the complete target extent, ordinary bytes, semantic fixups, and
private contributions. Most remaining mismatches come from compiler frame and
register choices, source-level declaration shape, unresolved data/call
bindings, and control-flow form. See the report for the largest observed
residue groups.

## Useful diagnostics

`tools/codegen_diff.py` aligns instructions and reports opcode counts,
register-only changes, immediates, memory operands, local displacements,
branch targets, instruction ordering, and the first structural difference.
Unknown indirect CFGs remain unknown. The diagnostic view accounts for LINK
transformations only when the strict matcher independently validates them. It
does not modify an object and does not participate in admission.

`codegen_grinder.py --evidence PATH` and `search.py` group candidates by raw
OMF identity. Reproducing an earlier object means the next experiment needs a
different source-shape or analysis hypothesis.
