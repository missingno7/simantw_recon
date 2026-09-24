# OpenMiniMapWin helper ownership audit

Read-only review of the preserved `_OpenMiniMapWin` and `_MapAreaEvent` packets, MAPSYM tables, symbol-address map, `evidence/topology/build-topology.json`, and `layout/private-data-topology.json`. No grinder, compiler, or proof-manifest command was run.

## Named near calls

The packet resolver displays unwrapped near-call destinations `0x11620` and `0x111e0`. For a 16-bit near call, reduce the computed destination modulo `0x10000`; the resulting MAPSYM offsets are `0x1620` and `0x11e0`:

- `_OpenMiniMapWin` at ANTEDIT offset `0xe374`: call bytes `E8 01 30` at `0xe61c` resolve to `0x1620`, `_CenterEdit` (MAPSYM offset 5664). Its `E8 A9 2B` call at `0xe634` resolves to `0x11e0`, `_UpdateEdit` (offset 4576). Further calls to `0x11e0` use the same symbol.
- `_MapAreaEvent` at offset `0xe100`: `E8 A6 33` at `0xe277` resolves to `_CenterEdit`; `E8 4E 2F` at `0xe28f` and `E8 E2 2E` at `0xe2fb` resolve to `_UpdateEdit`. Its separate `E8 43 2B` call at `0xe2e6` resolves to `_OpenEditWindow` (offset `0x0e2c`, MAPSYM 3628).

The symbol table marks all three as GAME-owned ANTEDIT_MODULE public symbols with PROBABLE confidence. The helper names are therefore already available; these call sites do not imply unnamed helper bodies.

## Object and ownership evidence

`build-topology.json` places `_MapAreaEvent`, `_Mini_MakeTable`, `_OpenMiniMapWin`, `_DrawMiniMapCursor`, `_EraseMiniMapCursor`, and `_ToggleMiniMapCursor` in component `antedit:E100`; its evidence includes 16 shared-slot joins. `_CenterEdit` and `_UpdateEdit` are in component `antedit:00F4`, whose evidence has 42 shared-slot joins plus one shared private-data join. This supports the callers and helpers belonging to different same-object components. It does not establish historical source filenames or a fully confirmed translation-unit boundary.

`_OpenMiniMapWin` is currently `ESCALATED` for `TRANSLATION_UNIT_CONTEXT_REQUIRED` with no production attempts. `_MapAreaEvent` is `ESCALATED` after two failed strict attempts with `TRANSLATION_UNIT_CONTEXT`. `_CenterEdit` is escalated; `_UpdateEdit` is not admitted. These statuses do not invalidate their MAPSYM public names or the near-call resolutions.

## Data and selector names

- `_OpenMiniMapWin` uses selector slot `C22C` for `_GamePaused` at PACK offset `0x9c28`; both the packet binding and MAPSYM agree.
- Selector slot `C228` is `_multiplier` at PACK offset `0x78ba`. The admitted `_Mini_MakeTable` source names this object and records its contribution at CONST `C228`.
- The caller component has pool words `C21E` through `C236` with gaps. `_MapAreaEvent` introduces `C21E`–`C22A`; `_OpenMiniMapWin` introduces `C22C`–`C236` and reuses `C224`, `C228`, and `C22A`. The component-level evidence supports their shared selector block.
- The packets name DGROUP operands `_MapPlane`, `_tileWidth`, `_tileHeight`, `_displayType`, `_editWidth`, `_editHeight`, and `_mmapCursorState` where local binding evidence permits. MAPSYM contains these symbols.
- `layout/private-data-topology.json` leaves selector words such as `C224`, `C22A`, and `C22E`–`C236` as `REFERENCE_CONSTRAINT` records with no historical name, object size, or candidate TU. It also leaves DGROUP operands `BCA8` (referenced by both callers) and `BCCE` (OpenMiniMapWin) unnamed and unsized. I found no tool evidence that assigns those words a stronger name or boundary.

## Limits

The proven helper public names are `_CenterEdit`, `_UpdateEdit`, and `_OpenEditWindow`; the public-call destinations are resolved by 16-bit wrap. The component evidence supports same-object grouping but does not prove a historical C translation unit. `_GamePaused` and `_multiplier` are exact selector/data bindings. The other listed private selector slots and unnamed DGROUP words remain unresolved, so this audit does not claim their data ownership or grant recovery credit.
