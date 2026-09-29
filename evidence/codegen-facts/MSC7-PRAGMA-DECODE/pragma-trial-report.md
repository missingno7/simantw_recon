# Per-function `#pragma optimize` trial

## Result

One pragma family reaches an exact function body: `_DecodeString` under its assigned `ogi` profile. `#pragma optimize("z", on)` and `#pragma optimize("n", off)` produce the same object hash and the same exact 172-byte body. The full member still fails strict proof because its private `_BSS` contribution is placed outside the original region. No tested setting reaches a strict complete-member match. No other public or static-helper frontier loses all its register and home differences.

The body hit is sufficient to treat the hypothesis as real and implement the requested review gate. It is not sufficient to approve `_DecodeString` in the review map: the full member must pass its BSS placement proof first. `layout/pragma-review.json` therefore remains empty.

## MSC 7.00 semantics

The pinned compiler accepts the syntax below. Compile success is not proof that a letter is meaningful: an unknown `q` is silently ignored and emits no diagnostic. The 1991 Microsoft C/C++ 7.0 manual documents `a,w,b0,b1,b2,c,g,e,l,x,z,n,p,r,s,t`; it does not document `i`, `y`, or `q` ([Programming Techniques manual](https://bitsavers.computerhistory.org/pdf/microsoft/msdos_c/Microsoft_C_7.0_1991/24775_Programming_Techniques_199111.pdf)).

| Setting | Pinned result and control |
|---|---|
| `optimize("", off)` | Changes the toy in all eight profiles: 106 bytes/frame 10 to 105/frame 8. |
| `optimize("e", off)` | Changes it in all profiles: 106/10 to 104/12 and removes saved DI/SI. This is a positive control for global register allocation. |
| `optimize("l", off)` | Changes it in all profiles: 106/10 to 80/4. `loop_opt(off)` produces the same object. |
| `optimize("t", off)` | Changes it in all profiles: 106/10 to 102/10. A separate syntax toy also changed from 48/4 to 46/4 under `t_off`; `s_on` produced that same output. |
| `optimize("g", off)` | No change in the generic toy, so that is a negative control. On the real admitted `win_SetColorFromObj` source under `/Og`, it changes the body from 114 to 112 bytes, a positive control. |
| `optimize("", on)` | Restores the active command-line profile. In the before/inside/after product probe, the wrapped function changed under `e_off`, the preceding function stayed byte-identical, and the following function returned to the default bytes after empty-on. |
| Other documented letters and forms | `a,w,b0,b1,b2,c,g,e,i,l,x,z,n,p,r,s,t` all compiled with `off` and `on`; most were output-identical on the syntax toy. `z_on` and `n_off` do change `_DecodeString` under `ogi`. |
| `i`, `y`, and unknown `q` | `i_off/on` under `/Oi` with a `strlen` toy made no observed change. `y_off/on` and `q_off` compiled without diagnostics and matched the toy control; their status is not inferred from parser acceptance. |
| `loop_opt(on)` | Compiles and restores the default loop behavior in the paired probe; per-function sweeps placed `loop_opt(on)` after `loop_opt(off)` so later source returned to default. |

The profile matrix covered all catalogued object profiles: `baseline` `/Oelw`, `og` `/Oeglw`, `ogi` `/Oegilw`, `ga` `/Oelw /GA`, `og-ga` `/Oeglw /GA`, `oi` `/Oeilw`, `oi-ga` `/Oeilw /GA`, and `ogi-ga` `/Oegilw /GA`. On the controlled loop/register toy, each profile produced the same control bytes and the same setting effects. The real `/Og` `win_SetColorFromObj` case establishes that a `g` effect depends on the function, not that `g_off` is inert.

Probe reports and specs are under `evidence/codegen-facts/MSC7-PRAGMA-P1/` through `MSC7-PRAGMA-P4/`. P1 records all eight profile runs, the letter syntax sweep (including the silent `q` negative control), and `/Oi` intrinsic checks. P2 records the before/inside/after locality and restore controls. P3 is the real `/Og` positive control. P4 compares `loop_opt(off/on)` with `optimize("l", off)`.

## Target sweep

Each public frontier came from `context.py --brief` and the best draft in the read-only main-repo worker tree when present. For each of the 16 open public targets, 47 sources were freshly compared under the assigned profile: control; documented individual letters `a,w,b0,b1,b2,c,g,e,i,l,x,z,n,p,r,s,t` with `off` and `on`; `e/g/l` combinations `eg`, `el`, `gl`, `egl` with `off` and `on`; empty-off/empty-on; and `loop_opt(off/on)`. Each wrapped function was followed by the corresponding restore. Results are opcode matches / target opcodes, candidate / target body bytes, and remaining register, stack-home, and branch differences.

| Function | Assigned profile | Best observed result | Outcome |
|---|---|---|---|
| `_AnimYellowFight` | baseline | 185/185, 545/545; 0 registers, 15 homes, 0 branches | No setting closed the 15 home differences. |
| `_FloodNestB` | baseline | 27/27, 60/60; 7 registers, 0 homes | No setting closed the register differences. |
| `_HoleBorder` | baseline | 36/36, 86/86; 11 registers, 0 homes | No setting closed the register differences. |
| `_WaitHundredths` | baseline | 22/22, 55/55; 4 registers, 0 homes | No setting corrected the register choices. |
| `_CarpetFloorR` | ogi | 76/76, 182/182; 0 registers, 1 home | No setting closed the home difference. |
| `_win_FindObject` | oi-ga | 45/45, 101/101; 10 registers, 0 homes | No setting closed the register differences. |
| `_GetAlarmDir` | og | 121/121, 286/286; 2 registers, 7 homes | No setting closed the register/home residue. |
| `_GtRegisterClass` | baseline | 32/32, 94/94; 0 registers, 13 homes | No setting closed the home differences. |
| `_CarpetFloorL` | ogi | 72/74, 179/181; 2 registers, 1 home | No setting improved the frontier to an exact body. |
| `_DecodeString` | ogi | `z_on` and `n_off`: 70/70, 172/172; 0 registers, 0 homes, 0 branches | Exact body and 9/9 fixups; full strict member fails only on private `_BSS` placement. Both settings share object hash `180b7e592adf553a9d6cb15d421ec7d88df79fced07ac43ddb3a7d21ca42b79a`. |
| `_SmoothAlarm` | og | 79/83, 195/187; 0 registers, 0 homes, 3 branches | No setting closed the control-flow/size residue. |
| `_RunTutor` | baseline | 59/68, 190/190; 1 register, 2 homes, 1 branch | No setting closed the residue. |
| `_win_MakeGroupSelectable` | baseline | 43/52, 112/125; 6 registers, 1 home, 3 branches | No setting closed the residue. |
| `_win_MakeGroupUnselectable` | baseline | 44/54, 125/125; 9 registers, 1 home | No setting closed the residue. |
| `_win_MakeGroupVisible` | baseline | `gl_on`: 43/52, 128/125; 1 register, 6 homes, 3 branches | Small register improvement; not close to exact. |
| `__font_StringWidth` | baseline | `loop_opt_off`: 39/90, 202/150; 4 registers, 6 homes, 2 branches | Worse than control (38/86, 192/150; 4 registers, 5 homes, 2 branches). |

`_InitAntLions` was already `MATCHED` in context, so it was not an open target and was not swept. The two antedit helpers were also compiled under `_UpdateEdit`'s assigned `/Oegilw` profile with the same settings, using the best read-only f2-chain-c drafts:

| Static helper | Control and best setting | Outcome |
|---|---|---|
| `3:6250` `UnnamedEditTileHelper` | Control 112/147, 401/430; best `g_off`/`gl_off` 112/147, 400/430; registers 12; homes 15 to 13 | A two-home improvement only; large immediate, memory, and branch residues remain. |
| `3:63FE` `DrawEditTileLeaf` | Control and best 289/315, 857/863; 9 registers, 24 homes | No setting improved the control; no exact body. |

No public target reached strict complete-member exactness; neither static helper reached diagnostic body exactness. Outside `_DecodeString`, no tested pragma closed an outstanding allocation residue; functions with no register/home differences remained structurally different for other reasons. Full per-setting results are in `build/workers/f-study-pragma/target-results/all.json` and `static-helper-results.json`.

## Consistency, clustering, and opposite model

Only `_DecodeString` has an exact body hit, so the hits do not cluster by object, profile, or author style. Its compiler unit is a singleton, with no existing member in that unit. I also compiled the admitted six-member `simant_5530_DoWinHelp_6_scaffold` unit plus the wrapped `_DecodeString` source under `ogi`. All original bytes in its `SIMANT_MODULE` (754-byte prefix), `POOLSTUB_TEXT` (144 bytes), and `RUN2_TEXT` (496 bytes) code contributions stayed identical; all 58 + 24 + 34 original code fixups were unchanged. This confirms the setting leaves the existing members untouched when the function is bracketed and restored. See `admitted-member-locality.json`.

The opposite model, compiling `_DecodeString` under whole-object `baseline` `/Oelw` and locally applying either `z_on` or `n_off`, was worse: both variants were 60/70 opcodes and 177/172 bytes, with 4 register and 3 branch differences. The assigned `ogi` profile plus one local setting is the only tested model that makes the body exact. Since `z_on` and `n_off` produce identical bytes, the historical spelling is not distinguished; both need one setting and one restore, so there is no evidence for a whole-object profile change or a multi-function pragma cluster.

## Review recommendation and gate

There is no currently admissible review entry. Pending a strict placement fix, the only candidate to investigate further is `_DecodeString` with:

```text
#pragma optimize("z", on)
#pragma optimize("", on)
```

Evidence: `build/workers/f-study-pragma/target-results/all.json`, the `_DecodeString` rows in `build/search/pragma-study/DecodeString/ogi/054598e18678/results.json`, and the P1 profile/letter probes. `#pragma optimize("n", off)` produces the same object hash, but neither setting has a complete-member proof. Do not populate the review map for this candidate until the `_BSS` placement is resolved and strict proof passes.

Implemented the fail-closed gate in `tools/promote.py`: only a listed function with exact `pragma_text`, exact empty-on `restore_text`, and existing repository-local evidence files passes; the pair must immediately bracket the function. The source sent to MSC is left intact, and all other pragmas remain rejected. `layout/pragma-review.json` has the required description and an empty `functions` map. `--steered TEXT` is mandatory for any reviewed pragma admission, and the review-map identity is added to promotion proof metadata. Tests in `tests/test_pragma_review_gate.py` cover listed/unlisted functions, changed setting text, required restore, and refusal of unrelated pragmas.

The focused pragma gate tests passed (6/6); the existing inline-assembly gate passed (5/5). `python tools/validate.py` ran 404 tests and ended with 7 errors and 7 failures. The failures are isolated-worktree evidence/environment issues: `build/recovered/manifest.json`, LINK `PARTLINK/receipt.json`, and a resource admission payload are absent; the `toolchain/` junction resolves outside this worktree and the LINK source check rejects it; the admitted `_IsThisEgg` source identity is stale; and runtime DGROUP placement tests lack the recorded placement evidence. Both pragma-review tests passed in the full run.
