# Code-generation infrastructure phase

The working profile remains MSC C/C++ 7.00 `/AL /G2 /Gs /Oelw`, with the original code-group name supplied through `/NT`. Historical patch identity is not a global recovery blocker.

The subsequent model handoff (retired on 2026-09-25; see [MIGRATION.md](../MIGRATION.md)) added a bounded task queue, compact context packets, validated compiler cache, crash recovery and strict promotion admission. Its end-to-end pilot adds `_IsItWall`; current source totals are **208 functions / 4,995 bytes**. The results below retain the infrastructure-phase milestones.

The phase report is [codegen-progress.json](codegen-progress.json). Independent source-recovery totals remain in [progress.json](progress.json). Generated scaffolding never enters those totals.

## Results

- Three previously blocked drafts now have independently rebuilt, complete OMF matches: `_DoWinHelp`, `_ProcMenuHelp`, and `_SetMenuOptionState`. Recovery is **207 functions / 4,969 code bytes**; runtime reuse remains **77 members / 12,960 bytes**.
- The combined menu-state TU matches **104 CODE bytes, 2 private CONST bytes, and all seven fixups**. Its historical filename is unknown. The grouping is `STRONGLY_SUPPORTED_TU`, not a claim to unique original boundaries.
- All **384** declaration/register/loop-test candidates for `db_GetObjectSize` compiled in **four historical boots**. Its best result remains **61/68 ordinary bytes, 7/7 fixups**, in an 84-byte contribution. The 68-byte figure is the ordinary-byte denominator, not total function length.
- Game extents with unknown size fell from the repository's actual starting **500 to 43**. The 457 improvements recognize unreachable NOP alignment gaps in otherwise closed recursive CFGs. They are `PROBABLE`, with gap ranges retained; they do not count as recovered source.
- All **41 frozen readable drafts** compiled as regression inputs. Three are now promoted and 38 remain unresolved. The baseline contained no complete matches: 40 mismatches and one unsupported comparison.
- The fingerprint suite has **164 cases**: 158 compile, while six explicit `memchr`/`_fmemchr` intrinsic requests are rejected by C7. It records REP STOSW, REP MOVSW/MOVSB, REPNE SCASB, pointer loads, cleanup instructions, relocations, and 312 string-instruction windows in historical libraries.
- Authentic LINK 5.30 produces a partial NE executable. Default code packing gives three segments; `/NOPACKCODE` preserves nine. SDK RC 3.00 successfully attaches a synthetic string resource in a separate executable. Both outputs are nonfunctional scaffolding, with zero recovery credit.

## Reproducible workflow

```powershell
python tools/codegen_grinder.py evidence/codegen/specs/DoWinHelp.json --out build/grinder/help --evidence evidence/codegen/runs/help-latest.json
python tools/codegen_grinder.py evidence/codegen/specs/db_GetObjectSize.json --out build/grinder/db
python tools/translation_units.py --spec evidence/codegen/specs/menu-tu.json --out build/tu/menu
python tools/codegen_fingerprints.py
python tools/codegen_regressions.py
python tools/cfg_solver.py
python tools/blocker_ledger.py
python tools/cards.py
python tools/translation_units.py
python tools/partial_link.py
python tools/partial_resources.py
python tools/codegen_report.py
python -m unittest discover -s tests -v
```

`tools/build.py` still constructs recovered objects, and `tools/verify_recovery.py` independently validates them. The build compiles identical TU recipes once per invocation; the structural linker deduplicates their object identities. Research tools never promote a source merely because it ranks first.

The grinder accepts a JSON specification with `symbol`, a source/template, explicitly allowed axes with rationales, compiler and flags. Axes can use audited generators (`u16_high_byte`, `local_order_register`) or an explicit bounded list of source forms. Prototype/type contrasts must state their assumptions; they are not automatically semantic equivalences. Duplicate sources are removed and candidate budgets are enforced.

Each candidate receives its own C source, compiler log, status marker, object identity and compile receipt. Full build-local results retain every comparison; `--evidence` stores every candidate's source/object identity plus a full representative of each distinct comparison. Scores include full-member literals, semantic fixups, private contributions, target/candidate extents, frames, pointer/cleanup features, and first divergence. Unsupported comparisons and compile failures remain explicit.

The batch worker mounts only construction and tool directories. It uses short DOS filenames, exclusive worker access, and a bounded queue of 96 jobs per session. Local unbounded trials stopped progressing around 160 jobs; increasing memory and separating command files did not fix this. The underlying cause is unresolved. Four boots for 384 candidates is the verified operating mode, not 384 boots or a claimed unlimited persistent worker.

## Reusable findings

### WinHelp argument shape and relocation chains

The original help drafts represented a far filename pointer and DWORD as independent words. They also hardcoded values such as `0x58a1` and `0x4e41` that are **NE relocation-chain links**, not historical segment constants. `_helpFile` is independently named in MAPSYM at PACK:76AC.

Declaring `helpFile` as a far character array and WinHelp's final argument as `unsigned long` lets C7 select the historical `MOV AH,[BP+7] / SUB AL,AL` sequence for the unsigned high-byte mask. The grinder finds multiple equivalent exact source forms. All four OMF fixups are now accounted for, including the filename's offset and selector.

The correct `ProcMenuHelp` member is 28 bytes: **27 function bytes plus one trailing alignment NOP**. Its complete OMF contribution matches. The prior 28-versus-27 comparison was not evidence that an extra byte necessarily preceded the far call. See the frozen baseline and complete-member comparisons for the actual distinction.

### Menu state and alleged shared tail

`SetMenuOptionState` tests **state != 0**, not state == 1. The unsigned comparison spelling remains a negative code-generation contrast. Compiling the two adjacent menu-state functions together naturally reproduces their public spacing and shared private CONST selector.

The apparent far-call target GR_MODULE:4C64 was an imported CheckMenuItem relocation-chain link. It is **not evidence of a shared executable tail**. Do not feed NE chain words into CFG target inference. Genuine branches, aliases, overlapping entry streams and cross-boundary tails have separate CFG evidence and classification.

### Cleanup and string idioms

In the tested ABI matrix, the baseline C7 cdecl wrappers emit `ADD SP,2`, the size-optimization contrast emits `POP BX`, and Pascal declarations emit no caller cleanup. None reproduces the historical `POP AX`. The result is reusable negative evidence; `_UnpackFileClose` remains unpromoted.

Typed indexed word-zero loops produce REP STOSW. Intrinsic memcpy variants produce REP MOVSW/MOVSB, and strlen variants produce REPNE SCASB. Plain pointer loops are not interchangeable with these idioms. Unsupported intrinsic declarations are recorded as failures, never treated as optimizer evidence.

The far-pointer suite tests far/huge character and void pointers, aggregate parameters, a state structure, and pointer-to-pointer assignment. No `_UnpackSetBuf` match was found. No direct caller was found in the mapped disassembly, so the original pointer type is still a hypothesis.

## Evidence and limits

- `evidence/codegen/corpus.json` and `corpus/`: immutable entry-state drafts.
- `evidence/codegen/corpus-results.json`: baseline compilation of every draft.
- `evidence/codegen/specs/`, `runs/`: controlled generators, choices, scores and receipts.
- `evidence/codegen/fingerprints.json`: ABI, pointer and string probes; historical-library windows and parser exclusions.
- `evidence/recovery/blockers.json`: specific causes, semantic hypotheses, correct bindings, best scores, failed experiments and next steps.
- `layout/translation-units.json`: supported compilation groups and confidence.
- `evidence/disassembly/cfg-extents.json`: recursive graph evidence, padding, branches, indirect jumps and aliases.
- `evidence/experiments/partial-link/`: LINK inputs, tool identities, stub inventory, maps/layout evidence and resource-processing contrast.

The structural link uses recovered objects, matched runtime members, historical CRT/FP/helper/import libraries, and explicit generated function/data scaffolding. Stub signatures and data capacities are not recovered ABI/type proof. The output has no reconstructed game behavior. No original EXE bytes are construction inputs.

Indirect jump tables remain `AMBIGUOUS_TABLE`; unresolved non-NOP gaps remain unknown. The strict recovery matchers were not relaxed to adopt CFG estimates. A confirmed recovered member containing a jump table can therefore retain an unresolved standalone CFG extent, as with `_CreateMonoSolidBrush`.

`InitSpider`, `ResetYellowVars`, `MakeRedInitiator`, the remaining register/frame cases, and the pointer/cleanup cases still need focused experiments. The infrastructure is in place for those experiments; their semantics have not been promoted as exact source.
