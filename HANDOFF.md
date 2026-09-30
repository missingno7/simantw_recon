# Handoff — 2026-09-30

## Mission (see AGENTS.md top)
SIMANTW.EXE is no longer being reconstructed to completion.
- The DOS reconstruction `D:\Prog\simant_recon` is the authority for the future SDL3 port. It is read-only for this project; another agent works on it.
- This repository only documents the Windows-specific host contract.
- Main deliverable: `docs/portable-windows-reference.md`.

## State at handoff
- **Image:** HYBRID_EXACT, debt 241,874 bytes (was 244,102 at the start of the 2026-09-29 orchestration phase), 468 tests pass, 0 claim conflicts. Everything is committed and pushed.
- **Game code:** 813 of 1,137 functions matched (109.8K of 311K bytes).
- **Scope:** by the port classification, 284 of the 324 unmatched functions (81% of open bytes) are out of scope: shared with DOS, or obsolete.
- **Classification:** `evidence/port/classification.json` (975 SHARED_WITH_DOS_IGNORE / 61 REQUIRED / 61 OPTIONAL / 40 OBSOLETE / 0 UNKNOWN).
  - Every REQUIRED item has its port question and an answer source.
  - `evidence/port/audit.json` holds per-function Windows API use and DOS pairing (`python tools/port_audit.py` regenerates it).

## Original-code analysis (done)
The Opus analysis of the original disassembly is folded into the spec as §0, with the evidence in `evidence/port/sections/ANSWERS.md`.
- It answers the MAINWNDPROC per-role dispatch, capture, win_Open/Close lifetime (WS_CHILD of rootWnd, create once / hide), auto-close, timer (MYTIMERFUNC, 17/170 ms, catch-up), paint and erase, and coordinates.
- It records 14 corrections to the drafts.
- No C reconstruction was needed.

## Next steps (priority)
1. Decode the window records from `win_LoadAllWindows` into tables for spec §B/§F: auto-close and modal flags, unassigned logical IDs, default geometry, kind-6 menus. Estimated about one day. Check first whether the DOS reconstruction already decodes them (read-only).
2. Start the SDL3 host prototype against the DOS reconstruction (outside this repository), implementing the §E API.
3. Byte matching: essentially none. Only when a host-contract question cannot be answered from the disassembly; the original-code analysis needed none.

## Tooling that stays useful
- `tools/context.py` (disassembly with resolved imports), `tools/port_audit.py`, `tools/xver.py` (DOS pairs, read-only), `tools/triage.py`.
- `tools/c2_emu.py` / `alloc_trace.py` / `alloc_search.py`: exact MSC 7.00 emulation and the allocator model.
- The orchestration layer (`sweep`, `attempts`, `fleet_plan`) for any focused reconstruction.
- Research facts: `docs/msc7-codegen.md` (MSC7-A5..A14, E27, M1..M7), `docs/msc7-allocator.md`, `docs/orchestration.md`.

## Worker conventions
- Luna workers (cx, gpt-6-luna) do mapping, inventory and documentation.
- Opus agents do boundary decisions and synthesis.
- No generic MSC7 tail grinding.
- The worker section drafts are preserved in `evidence/port/sections/`.
