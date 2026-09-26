# LZSS `/ND PACK` context probe

## Result

The hypothesis is **refuted as a module-wide compiler context**. MSC 7.00 `/NDPACK` places module near data in the PACK group and emits DS-indexed near-array accesses. Its prologue does not match the target selector source: the probe emits `push ds; mov ax, segment PACK; mov ds, ax`, with an OMF segment fixup to `PACK`. Target `_InsertNode` emits `push ds; mov ds, [0xB8DE]`; the selector comes from `_unpackHandle` in DGROUP. Target `_InitTree` starts `push di; mov es, [0xB8DE]` and has no DS save/load. A no-global far function compiled with `/NDPACK` still gets the PACK prologue, so the target `_InitTree` shape is a direct counterexample to the proposed automatic entry behavior.

## Compilation and layout

All code probes used authentic MSC 7.00 with `/AL /G2 /Gs /Oelw /NTSIMTWO_MODULE`, then compared that set with `/NDPACK` and the accepted separated spelling `/ND PACK`. The worker used one fixed flag list per batch. Probe sources are retained under `build/workers/lzss-1/`; `probe.json` contains exact source text and hashes, receipts, OMF groups/segments/fixups, probe code bytes, target bytes, and draft diagnostics.

| Source data | Baseline OMF | `/NDPACK` OMF |
| --- | --- | --- |
| File-scope uninitialized external declarations | DGROUP `_DATA`/`_BSS`; these are unresolved externals in C7 | PACK/PACK_BSS group; plain declarations remain external |
| `static` uninitialized arrays plus initialized public match words | DGROUP `_DATA` length 4 and `_BSS` length 29208 | PACK length 4 and PACK_BSS length 29208 |
| Zero-initialized arrays and match words | DGROUP `_DATA` length 29212 | PACK length 29212, PACK_BSS empty |
| Nonzero-initialized arrays and match words | DGROUP `_DATA` length 29212 | PACK length 29212, PACK_BSS empty |

With initialized near arrays the OMF public offsets are `_match_position` 0, `_match_length` 2, `_text_buf` 4, `_lson` 4118 (`0x1016`), `_rson` 12312 (`0x3018`), and `_dad` 21018 (`0x521A`), matching the reconstructed PACK layout. The near accesses use DS; code fixups target PACK contributions. The joined and separated `/ND` forms produced the same code bytes and group layout in paired probes.

## Alternative spellings tested

- `__loadds` under `/NDPACK` and `_loadds` under baseline load DS with a direct segment relocation (`PACK` or `_DATA`), not from `[B8DE]`.
- `__based(__segname("PACK"))` arrays/pointers compile through ES under baseline. Combining them with `/NDPACK` fails C1127 (`PACK` segment redefinition).
- `__based((__segment)unpackHandle)` array probes use ES from `_unpackHandle`; adding `/NDPACK` adds a separate direct DS prologue and leaves the based access on ES. Earlier local-`__segment` probes had the same ES result.

The nine preserved best drafts were recompiled under identical `/NDPACK` flags as a context check. None became a strict match; diagnostics are recorded in `probe.json`. Some tree diagnostics improved, but the extra direct-segment prologue and ES-based accesses do not reproduce the target selector load.

## Proposal

Do not add an `nd-pack` profile to `layout/compiler-profiles.json` for these components. `/NDPACK` explains the PACK placement and DS-near access in isolated probes, but is refuted as the target module-wide prologue context. `build/workers/lzss-1/profile-proposal.json` records the rejected candidate entry and exact singleton topology components/symbols. No catalog file was changed.
