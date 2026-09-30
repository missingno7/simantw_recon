# p2-events report

## C. Event translation: consequential open questions

- [UNKNOWN] Win16 MAINWNDPROC, WINMAIN, DoKeyDown, DoMouse, DoEvent, and MYTIMERFUNC remain open reconstructions. Their best drafts explain most of the event path, but the dispatch tables, argument packing, and exact event-record word names are not fully proved.
- [UNKNOWN] Confirm the timer callback lifecycle from the retail Win16 USER semantics: WINMAIN initially gives SetTimer a StopSimulation thunk; the admitted StopSimulation/RestartSimulation pair kills/drains and later restarts the timer with a null callback; the MainWndProc draft routes queued root WM_TIMER to MYTIMERFUNC. The exact first-tick ordering could affect an SDL fixed-step clock.
- [UNKNOWN] Confirm whether right-button down and right double-click reach DoMouse in any code path. MainWndProc’s best draft consumes WM_RBUTTONDOWN as the help toggle and forwards only WM_RBUTTONUP among right-button messages, while DoMouse’s draft recognizes all six button/down/up/double messages.
- [UNKNOWN] Establish which native/modeless dialogs need WM_CHAR/text editing. MainWndProc has no explicit WM_CHAR branch in its best draft, but standard Win16 dialog controls may have processed translated text outside this procedure.
- [UNKNOWN] Determine whether GTCLIENTWNDPROC’s DDE acknowledgement/data messages (0x03E4/0x03E5) are reachable in normal retail use or belong only to optional debug/legacy integration.
- [UNKNOWN] Pin the semantic source of Win16 event timing. MSG.time is available in the pump record, but current Do* drafts omit it; the DOS input ring stores a BIOS tick word.

## Port decisions supported now

- [INFERRED] Use one SDL event loop as the host queue pump and keep the existing logical window/object IDs above it.
- [INFERRED] Dispatch input through the current DoEvent family with normalized coordinates, keyboard modifiers, held-button state, and click phase; do not pass raw SDL events into gameplay routines.
- [INFERRED] Use SDL close/focus/resize/expose events for their host equivalents, with application-owned policy for quit veto, capture, timers, palette changes, and logical child activation.
- [VERIFIED] _win_Events and _win_FlushEvents have materially different semantics: one drains and dispatches every USER message while returning a narrow input flag; the other discards only selected input ranges. Preserve that distinction in the SDL adapter.
- [VERIFIED] The DOS authority has a queued Event record and main-loop dispatch keyed by code’s high byte. The portable host must feed that model rather than replacing the DOS event contract with HWND- or SDL_WindowID-based gameplay routing.

