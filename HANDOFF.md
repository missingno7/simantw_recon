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

## In flight at handoff
- **Opus analysis of the host-contract unknowns.** It reads the ORIGINAL disassembly (MAINWNDPROC dispatch per role, capture, win_Open/Close lifetime, auto-close, timer order, slot purposes, paint and erase). Its output lands in `build/workers/f-host-answers/ANSWERS.md` (ignored build dir; asm dumps are already there).
  - If it finished, merge it into `docs/portable-windows-reference.md` (§H step 1) and commit.
  - If not, rerun the same questions (they are listed in §F of the spec).

## Next steps (priority)
1. Fold ANSWERS.md into the spec and resolve §F items 1–4.
2. Decode the window-definition database objects (layouts by display type, kind-6 menus, slot purposes) into tables for §B.
3. Start the SDL3 host prototype against the DOS reconstruction (outside this repository), implementing the §E API.
4. Byte matching: only when a host-contract question cannot be answered from the disassembly. Candidates, if ever: MAINWNDPROC, win_Open, win_Close, win_GetEvent, DoMouse.

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
