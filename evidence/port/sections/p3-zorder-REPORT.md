# p3-zorder report

## Open questions that affect the SDL3 port

1. **Auto-close policy:** DOS byte-exact `f_218D_0451` closes a front logical window on an outside click when record bit `+0x1C & 1` is set, and closes it before bringing another stack window forward. The Win16 `_win_Open`, `_win_Close`, and `MAINWNDPROC` evidence is still draft-level and does not settle whether Win16 preserves this rule. The portable behavior authority is DOS, so implement the DOS rule in shared logic unless stronger Win16 evidence changes that conclusion.

2. **Capture release edge:** The best Win16 `MAINWNDPROC` draft captures on `WM_LBUTTONDOWN` (`0x0201`) and releases after `WM_RBUTTONUP` (`0x0205`), while custom dialogs and popup menus hold capture across their loops. Verify whether right-up is the only main-window release edge or whether a dropped/unmodeled path releases on left-up, capture loss, or a game event. This affects SDL capture lifetime and stuck-drag prevention.

3. **Z-order source with several SDL windows:** Win16 front tests query USER's live child/owner order; DOS tests its own `g_5702[]` order. SDL can request a raise, but it does not provide the same portable USER traversal. Decide whether external desktop raises should update the game order list or only focused/input-selected windows should. The SDL adapter will need explicit logical ordering either way.

4. **Exposure contract:** Win16 `win_IsWinExposed` means the entire logical client rectangle lies inside the root HWND rectangle; it does not detect occlusion by another SimAnt window. Confirm that the portable code should preserve this geometric test (recommended for DOS parity) rather than interpreting “exposed” as any visible/uncovered pixel region.

5. **Cursor assets:** Seven Win16 cursor resource names and their tool mapping are known, but the resource pixels and hotspots have not yet been inspected for SDL conversion. Extract those cursor resources for the native SDL cursor; keep the DOS software map cursor as a separate game-rendered overlay.

## Evidence quality

The DOS order, activation-on-click/auto-close rule, and `win_IsWinInFront` predicate come from exact sources. The Win16 `win_ToTop`, `win_IsWinInFront`, `win_IsWinExposed`, `_DoNextWindow`, cursor helpers, capture wrappers, `StillDown`, and `DoScenario` are admitted. `MAINWNDPROC`, `_DoMouse`, `_win_Open`, `_win_Close`, `_win_GetEvent`, and `ButtonHeld` remain open drafts; their behavior is labeled inferred in the section.
