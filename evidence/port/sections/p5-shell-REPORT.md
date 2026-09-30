# p5-shell report

[VERIFIED] Scope completed: sections 5 (window geometry), 7 (menus/ribbon/application shell), and 9 (Windows-only services), ready for `docs/portable-windows-reference.md`. Authored files are in `build/workers/p5-shell/`; the DOS project was read only. The Win16 packet was used as a semantic reference, not byte-matching evidence.

## Open questions that matter for SDL3

1. [UNKNOWN] **Per-window layout data:** decode the logical rectangles and anchor records for every selected type-9 database variant. The Win16 selector is clear (display types 9/10 split at desktop height 480), but SDL must decide whether that split follows DOS logical resolution or physical drawable size, and must use DOS-authoritative geometry for the default mode.
2. [UNKNOWN] **Complete menu command map:** recover each kind-6 menu row and accelerator ID to its DOS `ProcMenu` action, including popup-resource rows and checked/disabled state. The `0xFDxx` dispatch bridge is visible, but the exact label-to-action table is not proven by the open Win16 draft.
3. [UNKNOWN] **Resize policy:** decide which logical windows may resize, clamp, or scale under SDL. Win16 evidence explicitly recalculates logical window 0 and the bar/root host; it does not prove that every open panel reflows on every host resize. The DOS anchor/autosize algorithm is the behavior to compare against.
4. [UNKNOWN] **Placement persistence:** confirm from a complete `WINMAIN` source or later evidence that no SimAnt-specific window placement is saved. The current open draft persists options and button maps only and starts from screen metrics; this is strong evidence, not a complete proof of absence.
5. [UNKNOWN] **Optional host integrations:** decide whether portable help and external DDE interoperability are product requirements. Current evidence classifies WinHelp as an optional front end and DDE as outside the DOS game contract; no clipboard data API usage appears in the Win16 import audit.
