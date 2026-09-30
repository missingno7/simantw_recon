# Win16 SimAnt (SIMANTW.EXE) reference reconstruction

Mission (since 2026-09-30):
- This repository is the **Windows-specific reference** for a future portable SDL3 multi-window port of SimAnt.
- The DOS reconstruction (github missingno7/simant_recon) is the behavioural and visual authority for all shared game code.
- This project documents only how Maxis hosted its shared SimAnt window/object model on native Windows 3.1: windows, messages, painting, z-order, focus/capture, menus and shell, and the GDI boundary.

Start here:
- [HANDOFF.md](HANDOFF.md): current state and next steps.
- [docs/portable-windows-reference.md](docs/portable-windows-reference.md): the host-contract specification for the SDL3 port.
- [AGENTS.md](AGENTS.md): working rules, including the matching policy under the new mission.

## What exists

- **Exact reconstruction:** 813 of 1,137 game functions are rebuilt as readable C that authentic Microsoft C/C++ 7.00 compiles to the original bytes, fixups and placement. They are recorded in `src/recovery.json`, with sources in `src/recovered/`.
  - `python tools/image.py` rebuilds SIMANTW.EXE from the admitted objects plus explicit raw debt; it stays `HYBRID_EXACT`.
  - Totals are in `docs/progress.json` and `docs/image.json`.
- **Port reference:**
  - `evidence/port/` holds the per-function Windows API audit, the mission classification (975 functions shared with DOS / 61 required / 61 optional / 40 obsolete), the research sections, and the original-code answers.
  - `python tools/port_audit.py` regenerates the audit.
- **Compiler research:**
  - `docs/msc7-codegen.md` is the MSC 7.00 code-generation fact register.
  - `docs/msc7-allocator.md` describes the register allocator read out of C23216 under emulation; `tools/c2_emu.py` and `tools/alloc_trace.py` are its tools.
  - `docs/orchestration.md` covers the recovery orchestration tools.
- **Recovery workflow:** [docs/factory.md](docs/factory.md) (`context.py` → `search.py` → `promote.py`, `validate.py`). Under the new mission, use it only where exact code resolves a Windows-specific question.

## Setup and validation

Original assets and acquired tools stay local in the ignored `assets/` and `toolchain/`; `python tools/setup_toolchain.py` provisions the toolchain.

```powershell
python tools/validate.py          # tests, recovery verification, whole-image check (HYBRID_EXACT)
python tools/context.py SYMBOL    # original disassembly with resolved imports, calls and evidence
python tools/port_audit.py        # Windows API use and DOS pairing per function
```

Generated output goes to the ignored `build/` directory and is recreated on demand.
