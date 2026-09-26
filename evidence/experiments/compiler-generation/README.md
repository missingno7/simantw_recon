# MSC 6.00A versus MSC 7.00 generation sweep

## Scope and method

`python tools/context.py --list --open` returned **454 open GAME C targets**. Filtering the best preserved sources in `tools/drafts.py` for at least 85% opcode alignment selected **186 drafts**. Draft identity, source hash, topology component, resolved profile, and flags are recorded for every selected target in [`results.json`](results.json).

Each draft was freshly compiled under its resolved MSC 7.00 profile. The 7.00 flags follow `compiler_profiles.resolve`: `/AL /G2 /Gs`, the profile's optimization letters, and `/NT<original segment>`. The same `/A`, `/G`, `/Gs`, optimization letters, and `/NT` were passed to MSC 6.00A. Five `ga`-profile jobs omit only `/GA`: an MSC 6.00A probe returned warning D4002, "ignoring unknown flag -GA". The optimization-letter probes for baseline, `og`, and `ogi` were accepted without warnings. The pinned toolchain record continues to call 7.00 strongly supported for sampled game code and calls different game compilers possible but not required by tested probes.

`tools.compiler.compile_batch(..., compiler='msc700')` compiled all 186 7.00 jobs. I attempted the requested MSC 6.00A batch call; `compiler.py` rejected it with `FormatError: batch runner requires Win3.x compiler` because the pinned 6.00A DOS runner is not the Win3.x batch runner. I therefore compiled each 6.00A source with `tools.compiler.compile_source`, retaining fresh compiler receipts. No tools or catalog changes were made.

Every successful object was compared with `tools.library_match.compare_member`; the aligned target diagnostics were produced with `tools.codegen_diff.diagnose` and `render`, the path used by `search.py`. `results.json` records each compiler's compile receipt/outcome, strict result, literal bytes, fixups, opcode alignment, function byte lengths, diagnostic score, and first differing instruction. Full rendered alignments are preserved under `build/workers/compiler-sweep/diffs/`.

The per-target rank used for the component screen is lexicographic: complete-member success, `codegen_diff.score`, opcode match count, smaller absolute function-size delta, literal-byte equality ratio, fixup equality ratio, then fewer strict issues. A topology component was considered a pre-control candidate only when **every** MSC 7.00 non-exact near miss had both diagnostics, strictly improved this rank under MSC 6.00A, and had a strictly higher `codegen_diff.score`. A candidate then needed exact complete-member results for all admitted member sources compiled with MSC 6.00A, including equal literal bytes and fixups.

## Aggregate results

| Measure | Result |
| --- | ---: |
| Selected drafts | 186 |
| MSC 7.00 compiles | 186/186 |
| MSC 6.00A compiles | 170/186 (16 C2059 source parse failures) |
| Paired diagnostics available | 170 |
| `codegen_diff.score`: 6.00A higher / equal / lower | 7 / 21 / 142 |
| Opcode-alignment fraction: 6.00A higher / equal / lower | 5 / 26 / 139 |
| 6.00A strict complete-member matches from open drafts | 0 |
| Components clearing the strict pre-control screen | 2 |
| Admitted-source controls compiled / exact | 8 / 0 |
| Components passing controls | 0 |

Two 7.00 objects and two 6.00A objects compiled successfully but could not be placed by the strict matcher because a contribution exceeded the original extent. `codegen_diff` still produced aligned diagnostics and first-difference rows for all four; the strict comparison errors remain recorded per symbol. `_ShowIntro` has no differing instruction (`111/111` opcodes); its strict failure is the BSS contribution placement. No sweep compile reported an unsupported option after the `/GA` adjustment.

## Candidate components and controls

| Component | Near-miss evidence under 6.00A | Admitted-source control | Outcome |
| --- | --- | --- | --- |
| `simant1:9612` (`_GetSmellT`) | Score 0.782609 -> 0.922222; opcode alignment 45/46 -> 44/45; candidate function size 108 -> 106 bytes (target 106). | The component has no admitted sources to control. | No control evidence; not qualified. |
| `simtwo:78CA` (`_LessonDone`) | Score 0.546667 -> 0.557778; opcode matches 192/225 -> 197/225. | `_GiveLesson` control: 0/1 exact; `NO_COMPLETE_MATCH`, 696/744 literal bytes and 88/132 fixups equal, with conflicting private `CONST` placement. | Control failed. |

One additional component was close but did not pass the strict consistency screen: `simant:6A38` has `_SpecialXfer` at 0.780000 -> 0.782857 and `_YellowCommand` tied at 0.735683. Because every near miss must improve, the tie excludes the component. I also ran its seven admitted-source controls as a supplemental check; 0/7 were exact. All seven compare as `RULED_OUT_MEMBER`, with inconsistent public placements in `RUN3_TEXT` and `SIMANT_MODULE`.

No component passed, so no profile entry or context assignment is proposed. These are local diagnostic gains, not strict recovery evidence.

## Named residues

| Target | MSC 7.00 | MSC 6.00A |
| --- | --- | --- |
| `_WaitHundredths` (`gr:49E4`) | NO_COMPLETE_MATCH; 22/22 opcodes; 0.9091 score; 55/55 bytes; fixups 2/2 | NO_COMPLETE_MATCH; 22/22 opcodes; 0.9091 score; 55/55 bytes; fixups 2/2 |
| `_SetMapPlaneLocation` (`simant:9D04`) | NO_COMPLETE_MATCH; 133/133 opcodes; 0.9925 score; 419/419 bytes; fixups 45/45 | NO_COMPLETE_MATCH; 132/133 opcodes; 0.9850 score; 419/419 bytes; fixups 45/45 |
| `_GetSmellT` (`simant1:9612`) | NO_COMPLETE_MATCH; 45/46 opcodes; 0.7826 score; 108/106 bytes; fixups 2/12 | NO_COMPLETE_MATCH; 44/45 opcodes; 0.9222 score; 106/106 bytes; fixups 3/12 |
| `_HoleBorder` (`simone:16AE`) | NO_COMPLETE_MATCH; 36/37 opcodes; 0.6892 score; 88/86 bytes; fixups 8/8 | NO_COMPLETE_MATCH; 34/36 opcodes; 0.6667 score; 84/86 bytes; fixups 7/8 |
| `_LoadStringAnt` (`simone:03F4`) | NO_COMPLETE_MATCH; 93/94 opcodes; 0.8777 score; 231/231 bytes; fixups 7/7 | NO_COMPLETE_MATCH; 89/97 opcodes; 0.7990 score; 242/231 bytes; fixups 5/7 |
| `_musSoundBlasterClose` (`gr:7712`) | NO_COMPLETE_MATCH; 26/27 opcodes; 0.8519 score; 97/100 bytes; fixups 10/18 | compile failed |
| `_vocSoundBlasterClose` (`gr:7712`) | NO_COMPLETE_MATCH; 26/27 opcodes; 0.8519 score; 97/100 bytes; fixups 10/18 | compile failed |
| `_SoundBlasterMessage` (`gr:7712`) | NO_COMPLETE_MATCH; 88/95 opcodes; 0.7158 score; 297/296 bytes; fixups 1/39 | compile failed |

`_WaitHundredths` retains the reversed `add cx, ax` / target `add ax, cx` residue under both generations. `_SetMapPlaneLocation` loses opcode alignment under 6.00A (133/133 -> 132/133). `_GetSmellT` is the clearest local score gain, but it remains a strict near miss and its component has no admitted control. `_HoleBorder` and `_LoadStringAnt` get worse under 6.00A. The 6.00A compiler rejects the preserved C sources for `_musSoundBlasterClose`, `_vocSoundBlasterClose`, and `_SoundBlasterMessage` with C2059 syntax errors. `_MciMessage` is open but its best draft is 68/95 (71.6%), below the requested 85% cutoff, so it was not compiled in this sweep.

## Conclusion

This sweep does **not** support MSC 6.00A as the compiler for any tested topology component. Most paired diagnostics are worse under 6.00A; the two components that clear the strict pre-control screen have no available admitted control or fail their admitted-source control. The tested residues therefore remain assigned to the existing evidence-backed MSC 7.00 baseline. This result does not identify the compiler for untested components or settle the separate origin of individual library-looking functions.
