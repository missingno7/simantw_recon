# p6-classify report

## Result

[VERIFIED] Classified all 1,137 functions from evidence/port/audit.json; the original 528 non-SHARED proposals received a semantic-role decision and all 609 original SHARED proposals were retained after a 40-function stratified spot-check across every segment.

| final class | count |
|---|---:|
| SHARED_WITH_DOS_IGNORE | 975 |
| WINDOWS_PORT_REFERENCE_REQUIRED | 61 |
| WINDOWS_PORT_REFERENCE_OPTIONAL | 61 |
| OBSOLETE_WINDOWS_FEATURE | 40 |
| UNKNOWN_NEEDS_TRIAGE | 0 |

[INFERRED CLASSIFICATION] The audit’s import-only guess misclassified central host routines when an obsolete or incidental API appeared in the same function. _CleanUp and WINMAIN are REQUIRED despite WinHelp/printing/profile calls; _DoEvent and _YellowCommand are SHARED with a WinHelp-only delta; database/file, drawing, and Ralloc behavior remains DOS-owned; GDI display/palette/font choices, sound, file dialogs, diagnostics, and NetBIOS are OPTIONAL; WinHelp, DDE gateway, MCI, debugger traps, and Win16 global/local memory adapters are OBSOLETE.

[VERIFIED] Every REQUIRED item has either an admitted source or a preserved best draft, so no byte-exact reconstruction is needed solely to answer the host contract questions. See classification.md for all 61 questions and evidence paths.

## SDL3 questions that still need a design decision

1. [INFERRED PORT CHOICE] Queue semantics: win_FlushEvents removes mouse 0x0200-0x0209, keyboard 0x0100-0x0108, and WM_NCRBUTTONDOWN (0x00A4) messages; win_GetEvent dispatches until its stop condition. Decide whether the SDL bridge selectively filters equivalent stale input or normalizes/coalesces events while preserving order. Best-draft evidence: evidence/recovery/drafts/win_Open/340a8dee76c6.c:225-227 and evidence/recovery/drafts/win_GetEvent/bec22cc90795.c:102-135.
2. [INFERRED PORT CHOICE] Window identity: DOS window IDs index the shared object model and Win16 stores the associated HWND plus an INDEX property. Choose a stable SDL window table keyed by the same logical ID; use one SDL window per current HWND mapping unless the port intentionally changes the visible layout. Evidence: DOS docs/window-model.md:7-35 and Win16 best draft evidence/recovery/drafts/win_Open/340a8dee76c6.c:103-204.
3. [INFERRED PORT CHOICE] Capture/focus loss: Win16 distinguishes logical captureWnd from USER capture and only requests capture while active and non-iconic. Define how SDL focus loss/window close synthesizes release and resets the logical owner. Evidence: admitted src/recovered/MySetCapture-a20ced370b.c:16-25, src/recovered/MyReleaseCapture.c:5-10; main-window draft handles WM_MOUSEACTIVATE (0x0021) and activation changes.
4. [INFERRED PORT CHOICE] Damage strategy: Win16 ScrollWindow copies retained pixels then repaints exposed damage. Decide whether SDL uses renderer copy/scroll or a full redraw; DOS output is the visual authority, so compare final pixels while treating flicker/performance as separate port policy. Evidence: admitted src/recovered/wf_GBoxMove-31918745e5.c:44-49 and src/recovered/wf_PaintStuff-4a441706dd.c:39-63.

[INFERRED] These are SDL implementation choices, not unresolved Win16 source questions. The one less-settled source region is the non-byte-exact MAINWNDPROC best draft (1,360/1,742 aligned instructions); it already exposes the message cases needed for this contract. If the port later relies on an unmapped branch, focus RE on that branch rather than reopening the full function.

## Spot-check evidence

[VERIFIED] The deterministic sample is in classification-summary.json (6 from ANTEDIT_MODULE, 6 GR_MODULE, 6 SIMANT1_MODULE, 6 SIMANT_MODULE, 6 SIMONE_MODULE, 5 SIMTWO_MODULE, 5 _TEXT). All 40 have no direct Win16 imports and are game/simulation/database/resource/editor/object-model/drawing routines with DOS pair evidence; no sampled SHARED proposal was misclassified.

[VERIFIED] Read-only evidence used: DOS docs/window-model.md, docs/cross-version.md, layout/symbols.json, exact src/root/*.c, and cross-version correspondence; Win16 audit, src/recovery.json, admitted sources, best-draft index/sources, and SDK 3.00 WINDOWS.H.
