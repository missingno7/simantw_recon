# Win16 host-reference classification

Section for docs/portable-windows-reference.md (mission revision 2026-09-30).

## Final counts

[VERIFIED] These totals cover every function in evidence/port/audit.json after the semantic review.

| class | functions |
|---|---:|
| SHARED_WITH_DOS_IGNORE | 975 |
| WINDOWS_PORT_REFERENCE_REQUIRED | 61 |
| WINDOWS_PORT_REFERENCE_OPTIONAL | 61 |
| OBSOLETE_WINDOWS_FEATURE | 40 |
| UNKNOWN_NEEDS_TRIAGE | 0 |

## Contract boundary

[VERIFIED] The DOS implementation is the behavior authority for the shared window/object model. Its window record carries the client rectangle, object count, layout parameters, flags, and object-record pointers; object records carry anchoring modes, type, visibility/selection/dirty flags, and drawing data (DOS docs/window-model.md:7-35; exact DOS routines src/root/m20E8.c:207,259, src/root/m21FA.c:389, and src/root/m22BF.c:483,501).

[INFERRED] The Win16 adapter adds an HWND mapping per window bucket: win_Open indexes win_handles/win_hwnd with objectNumber >> 8, creates or reuses a GenericWindow, attaches its full SimAnt ID under the INDEX property, applies native geometry/menu/show state, then invalidates and updates it. The preserved best draft records these paths at evidence/recovery/drafts/win_Open/340a8dee76c6.c:89-227; _win_Open is still an open byte-recovery target, but the window-mapping answer is present.

[INFERRED] The Win16 message bridge uses GetMessage, accelerator handling, translation, and dispatch in that order (evidence/recovery/drafts/WINMAIN/8c89fbd1b287.c:250-255). win_GetEvent pumps PeekMessage/TranslateMessage/DispatchMessage and ends on left-button down/up or Space/- keydown, then derives the target SimAnt object from capture/INDEX and the pointer hit test (evidence/recovery/drafts/win_GetEvent/bec22cc90795.c:102-190).

[VERIFIED] The Win16 SDK header assigns WM_SIZE=0x0005, WM_PAINT=0x000F, WM_QUIT=0x0012, WM_MOUSEACTIVATE=0x0021, WM_GETMINMAXINFO=0x0024, WM_NCRBUTTONDOWN=0x00A4, WM_KEYDOWN=0x0100, WM_TIMER=0x0113, and left-button down/up 0x0201/0x0202 (toolchain/sdk300/INC/WINDOWS.H:1783,1792,1795,1809,1812,1842,1850,1863,1875-1876).

[INFERRED] The main-window best draft routes these messages through resize, activation/capture, timer, keyboard/mouse, palette, and paint paths (evidence/recovery/drafts/MAINWNDPROC/2512b5b9e4d8.c:292-887).

[VERIFIED] Painting is driven by the HWND update region: PaintStuff gets the INDEX property, snapshots the update region, brackets indexed-window drawing with BeginPaint/EndPaint, and restores GDI state (src/recovered/wf_PaintStuff-4a441706dd.c:39-63). GBoxMove uses ScrollWindow, collects and validates the exposed region, forces UpdateWindow, then deletes the temporary region (src/recovered/wf_GBoxMove-31918745e5.c:44-49).

[INFERRED PORT CONSTRAINT] SDL must preserve the resulting image; it may implement the scroll by copying retained pixels or by redrawing the whole dirty area.

[VERIFIED] Capture has both a logical SimAnt owner and an OS owner: MySetCapture stores captureWnd, requests USER capture only while active and not iconic, and accepts an OS capture handle only if it has INDEX; MyReleaseCapture clears the logical owner and calls ReleaseCapture while active (src/recovered/MySetCapture-a20ced370b.c:16-25, src/recovered/MyReleaseCapture.c:5-10, src/recovered/MyGetCapture.c:1-5).

## Required Win16 references

[VERIFIED] For each item, “Admitted source” or “Best draft” means its port question can be answered from preserved C evidence; exact byte recovery is not a prerequisite. “Needs focused reverse engineering” appears only when neither source is preserved.

| function | exact SDL host question | answer availability | source |
|---|---|---|---|
| MAINWNDPROC | Which WM_* messages enter SimAnt logic, and which update activation, size, capture, palette, title, and quit state? | Available — best draft | evidence/recovery/drafts/MAINWNDPROC/2512b5b9e4d8.c |
| MYTIMERFUNC | What does the timer callback update, and how does minimized/iconic state suppress drawing or change work? | Available — best draft | evidence/recovery/drafts/MYTIMERFUNC/fc256145b84f.c |
| WINMAIN | What startup sequence creates the application and what exact GetMessage/Translate/Dispatch and accelerator path ends on WM_QUIT? | Available — best draft | evidence/recovery/drafts/WINMAIN/8c89fbd1b287.c |
| _AdjustWndMinMax | What minimum tracking size and client/frame adjustments are written to WM_GETMINMAXINFO? | Available — best draft | evidence/recovery/drafts/AdjustWndMinMax/f875c046b912.c |
| _CleanUp | In what order are timers drained/killed, window properties removed, HWNDs destroyed, and platform services released? | Available — best draft | evidence/recovery/drafts/CleanUp/151a18301f6b.c |
| _DoBookMark | Does bookmarking raise a native window or only alter shared bookmark/game state, and what ordering is observable? | Available — best draft | evidence/recovery/drafts/DoBookMark/1fdca0f3fb96.c |
| _DoEditScroll | How are native scrollbar position/range values translated to the editor scroll model? | Available — best draft | evidence/recovery/drafts/DoEditScroll/8d75d29a356a.c |
| _DoEditScrollLine | How does a native scrollbar line notification change the editor model and repaint schedule? | Available — admitted source | src/recovered/tu_antedit_00F4_OverlayTileSet_27_reviewed-6edb3e7ce8.c |
| _DoExpMenu | Which experiment menu is opened and how are its client-relative coordinates transformed for popup tracking? | Available — admitted source | src/recovered/DoExpMenu-2fb0f20ceb.c |
| _DoKeyDown | How are WM_KEYDOWN/virtual keys, modifiers, cursor position, and pending queue messages turned into SimAnt actions? | Available — best draft | evidence/recovery/drafts/DoKeyDown/beeff18008b6.c |
| _DoMenuEntry | Which menu commands start/stop the simulation timer or close/reopen windows, and what IDs drive those actions? | Available — best draft | evidence/recovery/drafts/DoMenuEntry/456759648077.c |
| _DoMouse | How are mouse messages/button-state snapshots mapped to object hits, capture, z-order, and shared event callbacks? | Available — best draft | evidence/recovery/drafts/DoMouse/120cd296c0bf.c |
| _DoNextWindow | Which next HWND is selected, and how are visibility and z-order used when cycling windows? | Available — admitted source | src/recovered/tu_simant_01B6_DoUserButtonUpdate_15_reviewed-db9484741a.c |
| _DoUserButton | How do ribbon button IDs map to map/yard actions, and what capture/drag sequence surrounds reprogramming? | Available — best draft | evidence/recovery/drafts/DoUserButton/86e5f2b8b591.c |
| _EndGameDialog | How does the end-game path post application quit and coordinate with the shared dialog/window state? | Available — best draft | evidence/recovery/drafts/EndGameDialog/ddb59b96e42d.c |
| _GBoxMove | How does ScrollWindow move retained pixels and how are exposed damage regions validated and repainted? | Available — admitted source | src/recovered/wf_GBoxMove-31918745e5.c |
| _GetMousePos | Does the helper return screen or client coordinates, and which later conversion is expected by hit testing? | Available — admitted source | src/recovered/GetMousePos.c |
| _InitApplication | Which window class, procedure instance, cursor/icon, and class resources are registered at application startup? | Available — admitted source | src/recovered/tu_simant_01B6_DoUserButtonUpdate_15_reviewed-db9484741a.c |
| _InitInstance | How is the root HWND created, sized from client/system metrics, shown, and associated with the SimAnt root object? | Available — admitted source | src/recovered/tu_simant_01B6_DoUserButtonUpdate_15_reviewed-db9484741a.c |
| _InitMenu | Which native menus/submenus are created and attached to the root HWND? | Available — best draft | evidence/recovery/drafts/InitMenu/c16eb3494632.c |
| _InvalidUpdateEdit | Which editor HWND/rectangle is invalidated when its backing buffer changes? | Available — admitted source | src/recovered/tu_antedit_00F4_OverlayTileSet_27_reviewed-6edb3e7ce8.c |
| _MSClipEnd | Which selected GDI state and DC resources are restored/released after clipped drawing? | Available — admitted source | src/recovered/wf_MSClipEnd-48c3851864.c |
| _MSClipStart | Which HWND/DC/palette/clip state is acquired before clipped GDI drawing? | Available — admitted source | src/recovered/MSClipStart-6cff38c0cb.c |
| _MagnifyMenu | How is the magnification popup positioned relative to the owning HWND and converted between client/screen coordinates? | Available — admitted source | src/recovered/tu_antedit_67C6_MagnifyMenu_3_scaffold_split-abfeaa235b.c |
| _MyGetCapture | Where is the current capture owner represented and how is it mapped back to a SimAnt window/object? | Available — admitted source | src/recovered/MyGetCapture.c |
| _MyGetTopWindow | How does the adapter walk top-level/sibling HWNDs and filter them to a SimAnt window object? | Available — admitted source | src/recovered/wf_MyGetTopWindow-8cee2c18ed.c |
| _MyReleaseCapture | When is Win16 mouse capture released and which shared capture bookkeeping is cleared? | Available — admitted source | src/recovered/MyReleaseCapture.c |
| _MySetCapture | When does the adapter call SetCapture, and what does it return when capture is already held or a window is iconic? | Available — admitted source | src/recovered/MySetCapture-a20ced370b.c |
| _PaintStuff | How does WM_PAINT consume the update region, choose the object/window, and bracket drawing with BeginPaint/EndPaint? | Available — admitted source | src/recovered/wf_PaintStuff-4a441706dd.c |
| _PopUpInfoWindow | How is the information HWND created, sized, shown, and bound to its SimAnt object identity? | Available — best draft | evidence/recovery/drafts/PopUpInfoWindow/25f92df37eaf.c |
| _ProcMapRibbonEvent | Which map window is raised or selected when a ribbon event arrives, and what state is forwarded? | Available — admitted source | src/recovered/ProcMapRibbonEvent-8ce2938669.c |
| _ProcMenu | For each native menu command, which shared action runs, and when are HWND order, check marks, labels, and redraw updated around that action? | Available — best draft | evidence/recovery/drafts/ProcMenu/b14e50528ab7.c |
| _RedrawScreen | Which HWND/client region is invalidated and is UpdateWindow used to force immediate WM_PAINT? | Available — admitted source | src/recovered/RedrawScreen.c |
| _RedrawWindows | Which child HWNDs are enumerated and invalidated after shared state changes? | Available — admitted source | src/recovered/tu_simant_01B6_DoUserButtonUpdate_15_reviewed-db9484741a.c |
| _ResetEditScrollRange | Which scrollbar ranges and positions are published after editor content geometry changes? | Available — admitted source | src/recovered/tu_antedit_00F4_OverlayTileSet_27_reviewed-6edb3e7ce8.c |
| _RestartSimulation | Which timer ID, interval, and callback resume simulation? | Available — admitted source | src/recovered/tu_simant_0000_StopSimulation_2_reviewed-3d1e4706f3.c |
| _ScrollEditWindow | How are editor scroll deltas applied to the native client area and its update region? | Available — admitted source | src/recovered/wf_ScrollEditWindow-fe9b3200e2.c |
| _SetMenuItemState | How does shared menu state set/clear native check marks for one menu item? | Available — admitted source | src/recovered/menu_state_tu.c |
| _SetMenuOptionState | How does an option-state change update the native menu representation? | Available — admitted source | src/recovered/menu_state_tu.c |
| _SetMenuOptionText | How are menu option labels changed, including the identifier and redraw/update call? | Available — admitted source | src/recovered/SetMenuOptionText.c |
| _StopSimulation | Which timer is killed and which queued timer messages are removed when simulation stops? | Available — admitted source | src/recovered/tu_simant_0000_StopSimulation_2_reviewed-3d1e4706f3.c |
| _UpdateAllWindows | Does this function dispatch pending messages, synchronously paint invalid HWNDs, or both, and in what order? | Available — admitted source | src/recovered/tu_simtwo_C32E_win_ObjAddr_20_reviewed-cf86811e02.c |
| _UpdateEdit | Which dirty region is reused/scrolled versus redrawn for the editor, and when is the update forced? | Available — admitted source | src/recovered/tu_antedit_00F4_OverlayTileSet_27_reviewed-6edb3e7ce8.c |
| _UpdateEditIfBufInvalid | Which buffer-validity condition triggers a full editor repaint versus update-region reuse? | Available — admitted source | src/recovered/tu_antedit_00F4_OverlayTileSet_27_reviewed-6edb3e7ce8.c |
| _ms_PopUpMenuResource | How is a resource-backed popup menu created, positioned in screen coordinates, tracked, and destroyed? | Available — best draft | evidence/recovery/drafts/ms_PopUpMenuResource/c54c5e1ef272.c |
| _win_Close | How does closing a SimAnt window change HWND visibility, object state, and the next frontmost window? | Available — best draft | evidence/recovery/drafts/win_Close/cfc32202bfaa.c |
| _win_DoProxMenu | How does the proximity/context menu choose an owner HWND, pointer coordinates, and top-window ordering? | Available — best draft | evidence/recovery/drafts/win_DoProxMenu/04cb8cc044e8.c |
| _win_DrawTitle | Which SimAnt title/object field is copied to the HWND title bar, and when is SetWindowText called? | Available — best draft | evidence/recovery/drafts/win_DrawTitle/d5d4ad0d4bf3.c |
| _win_Events | Which queued messages are translated/dispatched by the event pump and how is termination detected? | Available — admitted source | src/recovered/tu_simtwo_C32E_win_ObjAddr_20_reviewed-cf86811e02.c |
| _win_FlushEvents | Which exact Win16 input-message ranges are removed from the queue, and which messages are preserved? | Available — admitted source | src/recovered/wf_win_FlushEvents-3010537d93.c |
| _win_GetEvent | How do button/key messages become DialogEvent values, and how is the target SimAnt object found under the pointer? | Available — best draft | evidence/recovery/drafts/win_GetEvent/bec22cc90795.c |
| _win_InvalidateObject | How does an object-level dirty flag/rectangle become an HWND invalidation request? | Available — admitted source | src/recovered/wf_win_InvalidateObject-69cbeedc5b.c |
| _win_IsWinExposed | How are window/client rectangles compared to decide whether any portion is exposed? | Available — admitted source | src/recovered/wf_win_IsWinExposed-22083a86a9.c |
| _win_IsWinInFront | How is a SimAnt window’s frontmost status derived from HWND order and visibility? | Available — admitted source | src/recovered/win_IsWinInFront-c38b403794.c |
| _win_IsWinOpen | What HWND/table state defines an open SimAnt window, and how is visibility treated? | Available — best draft | evidence/recovery/drafts/win_IsWinOpen/3d9036c5feb0.c |
| _win_IsWinZoomed | How does the wrapper report native zoom/maximize state for a SimAnt window? | Available — best draft | evidence/recovery/drafts/win_IsWinZoomed/ef1ad3bc179f.c |
| _win_LoadAllWindows | How are DOS-style window records loaded and mapped to Win16 HWNDs and initial geometry? | Available — admitted source | src/recovered/tu_simtwo_C32E_win_ObjAddr_20_reviewed-cf86811e02.c |
| _win_Open | How does a packed SimAnt window ID map through the handle bucket to create/reuse an HWND, geometry, properties, menu, and show state? | Available — best draft | evidence/recovery/drafts/win_Open/340a8dee76c6.c |
| _win_Swap | How are two SimAnt window IDs reflected in HWND identity, visibility, and object properties? | Available — best draft | evidence/recovery/drafts/win_Swap/a253085877ab.c |
| _win_ToTop | Which HWND is raised for a SimAnt window ID and what filtering happens first? | Available — admitted source | src/recovered/tu_simtwo_C32E_win_ObjAddr_20_reviewed-cf86811e02.c |
| _win_Zoom | Which ShowWindow command and object state implement zoom/restore? | Available — admitted source | src/recovered/win_Zoom.c |

## Classification method and spot-check

[VERIFIED] All 1,137 audit functions have a final class in evidence/port/classification.json; the 528 non-SHARED proposals were reviewed by behavior and API role. The original 609 SHARED proposals remain SHARED after a deterministic 40-function spot-check (seed 20260930), stratified across all seven segments; the sample and DOS-pair evidence are recorded in classification-summary.json.

[INFERRED CLASSIFICATION] Direct MessageBox, GetAsyncKeyState, file, database, bitmap, and UpdateWindow calls do not make game logic a host reference by themselves. Shared event/game/drawing/database/resource routines stay SHARED when the DOS source owns their behavior; the SDL adapter supplies normalized client coordinates and maps only lifecycle, queue, HWND identity/z-order, capture/focus, damage/paint, geometry, and menu behavior.

[VERIFIED] The DOS source has corresponding event/window operations (win_Open, win_Close, win_GetEvent, win_IsWinOpen, win_IsWinInFront) and shared DB/resource routines (OpenDB, db_LoadObject, DBRecall); see DOS docs/cross-version.md:44-49, src/root/m20E8.c:207-307, src/root/m22BF.c:483-607, and src/root/m1A28.c:45-119.
