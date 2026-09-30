# Win16 host contract: answers from the original SIMANTW.EXE code

Method: every answer below was read from the original binary's disassembly, not from C drafts. The packets came from `tools/context.py` and `evidence/disassembly/cards.jsonl`, with imports resolved through `toolchain/sdk300/WLIB/LIBW.LIB` and names from `assets/SIMANTW.SYM`. DS strings were read from segment 10 of `assets/SIMANTW.EXE`. Addresses are `segment:offset` inside the original segments; MAINWNDPROC is `SIMANT_MODULE:2930`. Annotated listings are next to this file: `MAINWNDPROC.asm`, `_win_Open.asm`, `_DoMouse.asm`, and the others (`dump.py`, `alldump.py`, `xref.py`, `ds.py` regenerate them). `all.asm` is every function, annotated.

Status key: **VERIFIED** means traced in original instructions. **UNKNOWN** means not settled, and the reason is given.

Two facts about the loader that were misread in earlier drafts:
- In the dumps, `push <reloc> ; _StopSimulation` followed by `push 0xNNNN` is only a segment-1 selector fixup. The fixup target names offset 0 of the segment, which is `_StopSimulation`. The real target is the immediate offset. `MakeProcInstance(seg1:0x2440)` is **MYTIMERFUNC** (WINMAIN `42CA`). `MakeProcInstance(seg1:0x1C38)` is **MYENUMFUNC** (MAINWNDPROC `2EC7`, `3B6B`, `3C17`).
- The unnamed DGROUP words below are private statics, named here only for description:
  - `0x376` is the "NC-active logical child" (`g_activeChild`).
  - `0x378`/`0x37A` hold the saved sound options.
  - `0x37C[8]` is the hover-popup ID table.
  - `0x38C` is the saved cursor.
  - `0x2EE`, `0x2F0` and `0x2F4` are timer counters and the re-entrancy guard.
  - `win_hwnd[]` is at `0xBCA6`, so `[0xBCA6 + 2*slot]` is the HWND of a slot: `0xBCA8` is slot 1, `0xBCB8` slot 9, `0xBCD8` slot 0x19, `0xBCEA` slot 0x22, `0xBCEC` slot 0x23.
  - `win_handles[]` (far record pointers, 4 bytes each) is at `0xCE9A`, so `[0xCF22]` is `win_handles[0x22]` and `[0xCF26]` is `win_handles[0x23]`.

---

## 0. Native window classes and HWNDs (the background for every answer)

**VERIFIED.** `InitApplication` (`SIMANT_MODULE:3DD0`, admitted) registers three classes. All three use `MAINWNDPROC` (`seg1:0x2930`).

| Class (DS string) | style | hbrBackground | icon/cursor |
|---|---|---|---|
| `AntRoot` (0x67C) | 0 (**no CS_DBLCLKS**) | `0x0D` = COLOR_APPWORKSPACE+1 | `LoadIcon(hInst,"SimAnt")`, IDC_ARROW |
| `GenericWindow` (0x684) | `0x1008` = CS_BYTEALIGNCLIENT\|CS_DBLCLKS | `6` = COLOR_WINDOW+1 | IDI_APPLICATION, IDC_ARROW |
| `RibbonWindow` (0x692) | `0x1008` | `GetStockObject(LTGRAY_BRUSH)` | IDI_APPLICATION, IDC_ARROW |

`InitInstance` (`3C8A`, admitted) creates these windows:
- **mainRootWnd**: class `AntRoot`, title "AntRoot". Style `0x02CF0000` (WS_OVERLAPPEDWINDOW\|WS_CLIPCHILDREN), no parent. It is placed at `(cx/100, cy/100)` with size 98% of the screen width by 90% of the screen height minus SM_CYICON. `SetProp(INDEX,-1)`, then `ShowWindow(nCmdShow|3)`, so it opens maximized.
- **ribbonBarWnd**: class `RibbonWindow`, style `0x52000000` (WS_CHILD\|WS_VISIBLE\|WS_CLIPCHILDREN), parent mainRootWnd, initially 0 high.
- **rootWnd**: class `AntRoot`, "SimAnt Root Window", style `0x52000000`, parent mainRootWnd, full client area. It has **no INDEX property**.

WINMAIN (`40FF-41AC`) then lays the frame out when `win_handles[0x22]` exists:
- `win_hwnd[0x22] = ribbonBarWnd`, and the ribbon gets `SetProp(INDEX,0x2200)`.
- The ribbon is sized to the client width × `rec(0x2200).bottom-top`.
- rootWnd is moved to `y = ribbonH` and sized to the client height minus `ribbonH`.

Every logical window is a **GenericWindow that is a WS_CHILD of rootWnd** (§3). The only other native windows are:
- `PopUpInfoWindow` (`_TEXT:610C`): a cached `GenericWindow`, style `0x54400000`, parent rootWnd, `INDEX=-1`.
- The COMMDLG/`DialogBox` file dialogs.
- The DDE client window.

`DestroyWindow` is called only in `CleanUp` (`SIMANT_MODULE:0050`) and `GtInitiateDDE`.

---

## 1. MAINWNDPROC message dispatch — VERIFIED

**Frame and parameters.** The procedure is `enter 0x1E4`, Pascal. The parameters are `hwnd=[bp+0E]`, `msg=[bp+0C]` (kept in `si`), `wParam=[bp+0A]` and `lParam=[bp+06/08]`. The dispatch compare tree runs from `293E` to `2A55`. The fall-through at `297D` works like this:
- If `msg == wSoundBlasterMsg` (the registered message at `DGROUP:0AF4`), it calls `SoundBlasterMessage(wParam,lParam)` and returns 0.
- Otherwise it goes to `3C6E`, which is `DefWindowProc(hwnd,msg,wParam,lParam)`.

**Messages not listed in the table go to DefWindowProc.** This includes WM_CREATE/DESTROY, **WM_ERASEBKGND (0x14)**, **WM_ACTIVATE (6)**, **WM_SETFOCUS/KILLFOCUS (7/8)**, **WM_KEYUP (0x101)**, **WM_CHAR (0x102)**, WM_SYSKEY*, WM_RBUTTONDBLCLK (0x206), all middle-button messages, WM_NCLBUTTON*, and WM_SETTEXT. The jump table at `29EE` sends 0x101–0x10F to `297D`.

| msg | entry | behaviour (all roles unless stated) | returns |
|---|---|---|---|
| WM_MOVE 3 | 2A58 | `UpdateEditIfBufInvalid()` | DefWindowProc |
| WM_SIZE 5 | 2A64 | `UpdateEditIfBufInvalid()`, then by role (see below) | DefWindowProc |
| WM_PAINT 0xF | 2CDC | see §7 | 0 / PaintStuff result / Def |
| WM_CLOSE 0x10 | 2DAA | see below | 1 or 0 / Def |
| WM_QUERYENDSESSION 0x11 | 2DBF | `KillTimer(rootWnd,0)`; if `MenuQuit()` returns nonzero: `CleanUp()`, return 1; else `SetTimer(rootWnd,0,17,lpTimerFunc)`, return 0 | 1/0 |
| WM_ACTIVATEAPP 0x1C | 2E40 | see below (Def if rootWnd==0) | Def |
| WM_SETCURSOR 0x20 | 3086 | see below | 0 or Def |
| WM_MOUSEACTIVATE 0x21 | 3140 | see below | 2 / 3 / Def |
| WM_CHILDACTIVATE 0x22 | 31C4 | root/ribbon/main: Def. Other windows: `SendMessage(g_activeChild,WM_NCACTIVATE,0)`, `SendMessage(hwnd,WM_NCACTIVATE,1)`, `g_activeChild=hwnd` | 0 |
| WM_GETMINMAXINFO 0x24 | 3218 | `win_hwnd[0]`: `AdjustWndMinMax(lParam)` (`SIMANT_MODULE:1A6E`). mainRootWnd: `ptMinTrackSize=(100,100)`. Others: Def | 0 / Def |
| WM_COMPACTING 0x41 | 324E | if `wParam>0x4000` and `GetFreeSpace(0)<50000`: `PopMsg("Memory is very low.")` | Def |
| WM_NCACTIVATE 0x86 | 327A | see below | 1 / Def |
| WM_NCRBUTTONDOWN 0xA4 | 330E | help toggle (same code as WM_RBUTTONDOWN) | 0 |
| WM_KEYDOWN 0x100 | 333E | if rootWnd: `DoKeyDown(hwnd,wParam,lParam)` (`SIMANT_MODULE:0E8C`) | **then** DefWindowProc |
| WM_COMMAND 0x111 | 3360 | see below | 1 / Def |
| WM_SYSCOMMAND 0x112 | 3662 | see below | 1 / Def result |
| WM_TIMER 0x113 | 37FE | `MYTIMERFUNC(hwnd,msg,0,0)`. In practice unreachable (§5) | 0 |
| WM_HSCROLL/VSCROLL 0x114/0x115 | 3810 | only for `win_hwnd[0]`: `DoEditScroll(hwnd,msg,wParam,lParam)`; for SB_LINEUP/LINEDOWN it repeats while `GetAsyncKeyState(VK_LBUTTON)` is down. Other windows: Def | 0 |
| WM_MOUSEMOVE 0x200 | 3870 | hover and proximity-popup handler, **not DoMouse** (see below). Ignored for rootWnd | 0 |
| WM_LBUTTONDOWN/UP/DBLCLK 0x201-0x203, WM_RBUTTONUP 0x205 | 3AEA | if rootWnd: `DoMouse(hwnd,msg,wParam,x,y)` (`SIMANT_MODULE:13F6`) | **then** DefWindowProc |
| WM_RBUTTONDOWN 0x204 | 330E | help toggle: `bHelp=!bHelp`; `SetCursor(bHelp ? hHelpCursor : GetClassWord(hwnd,GCW_HCURSOR))`. **Never reaches DoMouse** | 0 |
| WM_QUERYNEWPALETTE 0x30F | 3BC8 | if `paletteH`: GetDC, select and realize, restore, ReleaseDC. If the realized count is >0: `EnumChildWindows(rootWnd,MYENUMFUNC)` (InvalidateRect(child,NULL,FALSE) for visible children) and `InvalidateRect(ribbonBarWnd,NULL,FALSE)` | realized count |
| WM_PALETTECHANGED 0x311 | 3B0C | debug prints. If `wParam==hwnd`: return 0. If the app is inactive: the same enum and ribbon invalidate, return 0. If active: continue as WM_QUERYNEWPALETTE | |
| MM_WOM_DONE 0x3BD | 3BB6 | `MciMessage(wParam,lParam)` | 0 |

**WM_SIZE (2A64), by role:**
- **`win_hwnd[0]` (edit window), with wParam SIZE_RESTORED or SIZE_MAXIMIZED:**
  - It sets the wait cursor and erases the map cursor if slot 0x100 is open (MSClipStart/EraseMapCursor/MSClipEnd). It frees `editBuf`.
  - It rewrites record 0: `right = left + cx` and `bottom = top + cy + 0x12`. The logical rectangle includes an 18-px title strip. The first object's right and bottom move by the same deltas.
  - It then calls `win_Recalc(0)` and `UpdateEdit()`, redraws the map cursor, restores the cursor, and falls to Def.
- **mainRootWnd:**
  - `ribbonH` is the height of the ribbon's client rectangle, or 0 when there is no ribbon.
  - `SetWindowPos(rootWnd,0,0,0,cx,cy-ribbonH,SWP_NOMOVE|SWP_NOZORDER)`, then `screenWidth=cx` and `screenHeight=cy-ribbonH`.
  - `SetWindowPos(ribbon,…,cx,ribbonH,NOMOVE|NOZORDER)`, then `InvalidateRect(ribbon,NULL,TRUE)` and `UpdateWindow(ribbon)`.
- **rootWnd:** if `win_hwnd[0]` is zoomed:
  - If `(BYTE)GetVersion()==0xA3`, it calls `ShowWindow(SW_SHOWMAXIMIZED)`. That test never matches on Windows 3.x.
  - Otherwise it calls `SetWindowPos(win_hwnd[0],0,0,0,cx+2*SM_CXFRAME,cy+2*SM_CYFRAME,NOMOVE|NOZORDER)`.
- Other windows only fall to Def.

**WM_CLOSE (2DAA), by role:**
- mainRootWnd with rootWnd present: same as WM_QUERYENDSESSION. Returns 1 when it quits and 0 when cancelled; the timer restarts on cancel.
- mainRootWnd without rootWnd: Def.
- rootWnd and ribbon: Def.
- Any other window whose `GetProp(INDEX)` is not −1: `win_Close(INDEX)`, return 1. The native window is never destroyed.

**WM_ACTIVATEAPP (2E40).**

Activation (wParam≠0):
1. `SetUpPalette(1)` and `activeAppFlag=1`.
2. If `g_activeChild==0`, it becomes `MyGetTopWindow(rootWnd)`. It is then sent `WM_NCACTIVATE(1)`.
3. The sound options are restored. If `paletteFlag` is set: `EnumChildWindows(rootWnd,MYENUMFUNC)` and `InvalidateRect(ribbon,NULL,FALSE)`.
4. `SetFocus(rootWnd)`.
5. If `captureWnd` exists, `mainRootWnd` exists and `IsWindowVisible(captureWnd)`: when the main window is not iconic, `SetCapture(captureWnd)`. In either case, `BringWindowToTop(captureWnd)`.
6. `win_FlushEvents()`.
7. `KillTimer(rootWnd,0)`, then `SetTimer(rootWnd,0,17,lpTimerFunc)` if `lpTimerFunc` is set.
8. `SetCursor(saved)`, then Def.

Deactivation:
1. It saves the cursor and sets IDC_ARROW.
2. `KillTimer`, then `SetTimer(rootWnd,0,**170**,lpTimerFunc)`.
3. If `captureWnd`: `ReleaseCapture()`. `captureWnd` is **kept**.
4. `SetUpPalette(0)` and `StopSong()`.
5. If the app was active, it saves the song/effect options and zeroes them (`OptionStates+2/+4`, `songsOnFlag`, `effectsOnFlag`).
6. `SendMessage(g_activeChild,WM_NCACTIVATE,0)`, then `activeAppFlag=0`, then Def.

**WM_SETCURSOR (3086).**
- If `bHelp` is set: `SetCursor(hHelpCursor)`, return 0.
- Otherwise it sets a tool cursor when all of these hold:
  - the cursor is over `win_hwnd[0]` and slot 0 is in front, **or** over `win_hwnd[1]` with slot 0x100 in front and Shift held;
  - `LOWORD(lParam)==HTCLIENT`;
  - `CurGameType==3`.
- The tool cursor is `SetCursor(mag/rock/dig/ant/food/drop/spray [CurExpTool 0..6])`, and it returns 0. In every other case, Def (the class cursor, IDC_ARROW).

**WM_MOUSEACTIVATE (3140).**
- If hwnd is rootWnd, the ribbon, mainRootWnd or `g_activeChild`: Def.
- If `HIWORD(lParam)` is not WM_LBUTTONDOWN: Def.
- Otherwise it looks up the INDEX of `MyGetTopWindow(rootWnd)`:
  - If the INDEX is not −1 and the top record's `+0x1C & 0x40` is clear: `BringWindowToTop(hwnd)`, `SendMessage(hwnd,WM_NCACTIVATE,1)`, return **2 = MA_ACTIVATEANDEAT**. The first click on a background logical window only raises it.
  - Otherwise return **3 = MA_NOACTIVATE**. The click is delivered, but DoMouse ignores it because hwnd is not the top window. The 0x40 bit is the modal flag.

**WM_NCACTIVATE (327A).**
1. `UpdateEditIfBufInvalid()`.
2. If `!activeAppFlag`, return 1 (no default caption repaint).
3. If `wParam==0`, Def.
4. If hwnd is `win_hwnd[0]` and 0x2300 is open: `win_Swap(0x2300→0x2200)`, `UpdateWindow(win_hwnd[0x22])`, `DrawMapData()`.
5. If hwnd is `win_hwnd[0x19]` and 0x2200 is open: `win_Swap(0x2200→0x2300)`, `UpdateLayQueenModeDisplay()`, `UpdateWindow(win_hwnd[0x23])`, `DrawYardData()`.
6. Then Def.

**WM_COMMAND (3360)** (accelerators reach it through `TranslateAccelerator(rootWnd,…)` in WINMAIN).
- **`0xFDA0-0xFDAC`** act on `top=MyGetTopWindow(rootWnd)`, which must be nonzero. Each returns 1.

  | ID | action |
  |---|---|
  | A0 | `SendMessage(top,WM_CLOSE)` |
  | A1 | `SendMessage(top,WM_SYSCOMMAND,SC_KEYMENU)` |
  | A2 | cycle: bring the bottom-most visible, unowned sibling to the top |
  | A3 | SC_MOVE |
  | A4 | SC_SIZE, only if top is slot 0 |
  | A5 | slot 0 only: toggle between SW_SHOWNORMAL and SW_SHOWMAXIMIZED |
  | A6–A9 | line-scroll the edit window up/down/left/right with `DoEditScroll`, repeating while Ctrl+arrow is held |
  | AB | About MessageBox |
  | AC | capture-debug MessageBox; then `ReleaseCapture` and `win_Close(INDEX of the capture window)` |
- Other `0xFDxx` IDs call `DoMenuEntry(wParam)` and return 1.
- `0xF9xx` IDs store the low byte in `popUpMenuId` and return 1.
- Anything else goes to Def.

**WM_SYSCOMMAND (3662).**
- **mainRootWnd:**
  - SC_MINIMIZE: `ReleaseCapture` if `captureWnd`, then the common path.
  - SC_CLOSE: `KillTimer`, `MenuQuit`. If it confirms: `CleanUp`, return 1. If cancelled: `SetTimer`, return 1.
- **Other windows:**
  - SC_NEXTWINDOW brings the bottom-most visible, unowned child to the top and returns 1.
  - SC_CLOSE on `win_hwnd[0x19]` calls `YardToMap()` first.
- **Common path (3734):** `KillTimer(rootWnd,0)`, `DefWindowProc`, then restart the timer at 17 ms. This covers the modal move/size/menu loops. Then, only for mainRootWnd with SC_RESTORE and a `captureWnd`: `SetCapture(captureWnd)` and centre `captureWnd` in the rootWnd client area (`SetWindowPos(…,SWP_NOSIZE|SWP_NOZORDER)`).

**WM_MOUSEMOVE (3870).**
1. The point is converted with `ClientToScreen`, then `WindowFromPoint`.
2. `obj = win_FindObject(GetProp(hit,INDEX), point in hit's client)`.
3. Hover-highlight: an object with flag `+0x24&0x10` is inverted with `win_ObjInv` inside `MSClipStart(hwnd of the openSub window)`, or `_win_SetProxItem` is called.
4. **Only when the hit window is `win_hwnd[9]`** (the 0x0900 tool/proximity menu): `i = (win_GetProxEvent()&0xFF)-2`, and if `0<=i<=7` and `table[i] != openSub`:
   - it closes the previous popup (`MyReleaseCapture`, `win_Close(openSub)`, `UpdateAllWindows`);
   - it opens `table[i]` at object `0x902+i`'s top-left, converted to rootWnd client coordinates;
   - it calls `MySetCapture(new hwnd)`.
   - The table is `DS:037C` = {‑1, 0x0C00, 0x0F00, 0x1000, 0x1100, 0x0D00, 0x0E00, ‑1}.
   - If the entry is −1 or unchanged, it calls `MySetCapture(win_hwnd[9])`.

---

## 2. Mouse capture — VERIFIED

Every SetCapture and ReleaseCapture site, from the relocation xref:
- **SetCapture:**
  - MAINWNDPROC `2F3C` (ACTIVATEAPP restore);
  - MAINWNDPROC `3789` (SC_RESTORE on main);
  - `MySetCapture` `GR_MODULE:45A5`;
  - `INDIRECTDLGPROC` `DE33`.
- **ReleaseCapture:**
  - MAINWNDPROC `3000` (deactivate);
  - MAINWNDPROC `368A` (SC_MINIMIZE on main);
  - MAINWNDPROC `3626` (0xFDAC debug);
  - `MyReleaseCapture` `45E9`;
  - `WINMAIN` `4469` (exit, if GetCapture);
  - `INDIRECTDLGPROC` `DE49`.
- **The wrappers:**
  - `MySetCapture(hwnd)` always stores `captureWnd=hwnd`. It calls USER SetCapture only if `activeAppFlag` is set and the main window is not iconic.
  - `MyReleaseCapture()` clears `captureWnd` and calls ReleaseCapture only if the app is active.
  - `MyGetCapture()` returns `captureWnd`, not USER's capture.
- **Callers of MySetCapture:**
  - MAINWNDPROC hover (`3AC3`, `3ADE`);
  - `win_DoProxMenu`, AboutDialog, DoExpMenu, DoScenario, DoUserButton, DrawCastePopUp, EndGameDialog, LionDialog, MagnifyMenu, OpenMiniMapWin, PictureDialog, ScoreDialog, ShowIntro, SpecialXfer, SpiderDialog, YellowDialog.
  - The same routines call MyReleaseCapture when their loops end. MAINWNDPROC also calls it at `3A1E` when switching hover popups.
- **MAINWNDPROC does not capture on WM_LBUTTONDOWN, and no button-up releases capture.** WM_LBUTTONUP and WM_RBUTTONUP only go to DoMouse. `_DoMouse`, `_win_GetEvent`, `StillDown` and `ButtonHeld` contain no capture calls. Drags are done by polling:
  - `StillDown` and `ButtonHeld` read `GetAsyncKeyState`. Bit 1 is LBUTTON, Insert or Space. Bit 2 is RBUTTON or Delete. Both honour `SwapMouseButton`.
  - `win_GetEvent` targets `MyGetCapture()`, or the top visible child if there is no capture.
- **Right button:**
  - WM_RBUTTONDOWN and WM_NCRBUTTONDOWN toggle help mode and never reach DoMouse.
  - WM_RBUTTONUP reaches DoMouse, but DoMouse only updates `mouse_state` for up messages. **Neither button's up message produces a DoEvent** (DoMouse returns at `1782`).
  - WM_RBUTTONDBLCLK goes to DefWindowProc.
  - So the right button produces no DoEvent in Win16. It is only visible through the polled button word: DoMouse's `buttons` field bit 2 and StillDown.
- **On deactivation,** native capture is released but `captureWnd` survives. On reactivation it is re-set if the window is visible and the main window is not iconic, and the window is always raised.
- **INDIRECTDLGPROC** (`SIMTWO_MODULE:DDD2`) sets capture on WM_INITDIALOG and releases it on WM_LBUTTONDOWN, then EndDialog. **Nothing references it.** Its offset does not appear as an immediate anywhere, and no DialogBoxIndirect or CreateDialog import is used. So it is unreachable in retail. SimAnt's "dialogs" are logical GenericWindows with MySetCapture and a `win_GetEvent`/`win_Events` loop.

---

## 3. win_Open / win_Close — VERIFIED

`win_Open(id, a, b, c, d)` is at `SIMTWO_MODULE:CA2E`. The record is `win_handles[id>>8]`.
- **Record update:** it stores `a..d` at record `+0x10..+0x16` and calls `win_Recalc(id)`. It sets the open flag `+0x1D |= 2`.
- **Rectangle conversion:**
  - `yoff = ribbonBarHeight`, unless the first object's `+0x18 == 5`. **`_ribbonBarHeight` (DGROUP `0xBD0A`) is 0 in the data segment, and no instruction writes it.** So in retail no ribbon offset is applied and the record rectangle is used directly as rootWnd client coordinates.
  - The frame adds size through GetSystemMetrics (`CB00-CB8F`), depending on the record flags:
    - `+0x1C&8`: style gains WS_THICKFRAME\|WS_HSCROLL\|WS_VSCROLL; `cx += 2*SM_CXFRAME + SM_CXVSCROLL` and `cy += 2*SM_CYFRAME + SM_CYHSCROLL`.
    - Else `+0x1C&4`: WS_CAPTION\|WS_SYSMENU\|WS_BORDER; `cy += SM_CYCAPTION - 18 + 2*SM_CYBORDER` and `cx += 2*SM_CXBORDER`. The 18-px logical title strip becomes the native caption.
    - Else: WS_DLGFRAME; `cx/cy += 2*(border + dlgframe)`.
  - The final rectangle is `x = rec.left`, `y = rec.top - yoff`, `cx = w + dx`, `cy = h + dy`.
- **Existing HWND (`win_hwnd[slot] != 0`):**
  - If visible: `BringWindowToTop` only.
  - If hidden: when the first object's anchor fields `+0x18..+0x1E` are 0 or equal to `id`, and its type is not 5, it calls `BringWindowToTop` and `ShowWindow(IsZoomed ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL)`. Otherwise it calls `SetWindowPos(hwnd,HWND_TOP,x,y,cx,cy,SWP_FRAMECHANGED)`, `BringWindowToTop`, `ShowWindow(SW_SHOWNORMAL)`.
  - Then `UpdateWindow`.
- **First open (create once):**
  - Extra style bits come from the record flags: `+0x1C&0x10` adds CAPTION\|SYSMENU\|MINIMIZEBOX; `+0x1C&0x80` adds WS_MAXIMIZE; `+0x1D&1` adds CAPTION\|SYSMENU\|MAXIMIZEBOX.
  - **The style always gets `|= 0x44000000` = WS_CHILD\|WS_CLIPSIBLINGS** (`CD1A`).
  - The title comes from the first object of type 0x0C (inline text at `+0x2A`) or type 0x12 (far pointer, or inline `+0x2E` if it contains no '%'). Either one adds WS_CAPTION. Otherwise the title is "Generic Window".
  - The call is `CreateWindow("GenericWindow", title, style, x,y,cx,cy, **parent=rootWnd**, menu 0, hInst, 0)`.
  - Then `win_hwnd[slot]=hwnd` and `SetProp(hwnd,"INDEX",id)`.
  - If WS_SYSMENU is set, the system menu is rebuilt: it inserts "&Close\tCtrl+F4" (SC_CLOSE), removes SC_TASKLIST and the last item, and appends a separator and "Nex&t\tCtrl+F6" (SC_NEXTWINDOW).
  - Then `BringWindowToTop`, `ShowWindow(SW_SHOW)`, `InvalidateRect(NULL,TRUE)`, `UpdateWindow`.
- **Owner:** these are child windows, so there is no owner. The `GW_OWNER` step in the z-order helpers is a no-op for them.
- **Always at the end:** `clip_Off()`, `win_UnlockWin(id)`, then the queue is drained with `PeekMessage(PM_REMOVE)` loops over WM_MOUSEFIRST..0x209, WM_KEYFIRST..0x108 and 0x21. This is the same as `win_FlushEvents`. Every `win_Open` discards all queued mouse and keyboard input, including when the window was already visible.

`win_Close(id)` is at `CF98`.
- If `win_hwnd[slot]` exists: it clears `+0x1D&~2` and calls `ShowWindow(hwnd,SW_HIDE)`. The **HWND is kept; the window is never destroyed.**
- To choose the next window, it walks from `GetTopWindow(rootWnd)` to the first visible child (following GW_OWNER if one exists). It calls `BringWindowToTop(that)` and `SendMessage(that,WM_NCACTIVATE,activeAppFlag,0)`.
- A BringWindowToTop on a child also generates WM_CHILDACTIVATE, which updates `g_activeChild`. That step follows from USER semantics, not from code in the binary.

**INDEX property.** It is set in:
- `win_Open` (`CE69`);
- `win_Swap` (`D55E`), which moves one HWND from logical ID `from` to `to` and hides nothing;
- WINMAIN, ribbon=0x2200 (`4132`);
- InitInstance, mainRootWnd=−1;
- PopUpInfoWindow, −1;
- INDIRECTDLGPROC.

It is read by:
- MAINWNDPROC: WM_PAINT (−1 goes to Def), WM_CLOSE (win_Close), WM_MOUSEACTIVATE (the top record's 0x40 flag), WM_MOUSEMOVE, and the 0xFDAC path;
- DoMouse, DoKeyDown, win_GetEvent, MySetCapture (validation), PaintStuff (`win_DrawWindow(INDEX)`).

`RemoveProp` is called only in `CleanUp`.

---

## 4. Auto-close (DOS `+0x1C bit 0`) — VERIFIED (a different mechanism from DOS)

Win16 implements a variant in **`_DoMouse` (`SIMANT_MODULE:1445-1463`)**:
1. DoMouse first requires `hwnd == MyGetTopWindow(rootWnd)`, or hwnd to be the ribbon.
2. Then, `if (msg==WM_LBUTTONDOWN && record(INDEX)+0x1C & 1) { win_Close(INDEX); return; }`.

There is **no inside/outside rectangle test.** Any left-button-down delivered to the top bit-0 window closes it, and the click is consumed before any object hit test.

An *outside* click reaches that window only when it holds capture, which the popup and menu routines take with MySetCapture. Without capture:
- An outside click on another logical window goes through WM_MOUSEACTIVATE (`3171-31C1`). The clicked window is raised, the click is eaten, and **the bit-0 window stays open underneath.**
- If the top record has `+0x1C&0x40`, the click is not activated and DoMouse ignores it. This matches DOS `noClose`.
- Clicks on empty rootWnd are ignored: DoMouse returns when `hwnd==rootWnd`.

Consequence for the port: DOS remains the authority. If the SDL port keeps the DOS rule (outside click with bit 0 set closes the front window), it differs from Win16 in two cases: an inside click on a bit-0 window, and an uncaptured outside click.

**UNKNOWN:** which windows set bit 0 or bit 0x40. That is resource data (the `win_LoadAllWindows` records), not code, and needs a record decode rather than a C reconstruction.

---

## 5. Timer and loop — VERIFIED

- **Only one timer exists:** ID **0** on **rootWnd**, always with the callback `lpTimerFunc = MakeProcInstance(MYTIMERFUNC)` (WINMAIN `42CA-42DC`). No site passes a NULL callback.
- **SetTimer sites:**
  - WINMAIN `43EF`, 17 ms;
  - RestartSimulation `004A`;
  - MAINWNDPROC `2DF0` (quit cancelled), `2F91` (activate, 17), `2FF4` (deactivate, **170 ms**), `36B8` (SC_CLOSE cancelled) and `376E` (after DefWindowProc in WM_SYSCOMMAND);
  - `DoMenuEntry` `1A5E` and `DoUserButton` `0857`, after Save/Load/Quit.
- **KillTimer sites:**
  - StopSimulation, which also drains WM_TIMER with `PeekMessage(PM_REMOVE|PM_NOYIELD)`;
  - CleanUp, Punt, DoMenuEntry (×4), DoUserButton;
  - MAINWNDPROC around quit, activation and system commands.
- **StopSimulation and RestartSimulation** keep a nesting count (`DGROUP:0044`). The timer is killed on the first stop and restarted when the count returns to zero.
- **Callback, not WM_TIMER:** because a callback is given, DispatchMessage calls MYTIMERFUNC directly. MAINWNDPROC's WM_TIMER branch (`37FE`) is never reached in practice.
- **Start-up order:**
  1. InitApplication, then InitInstance (the frame is shown and UpdateWindow is called).
  2. Palette detection, `IBMInitStuff`, ribbon layout, the database, `snd_Install`, the INI reads.
  3. **`ShowIntro`, `CustomerIDDialog`, `NewGame(1)`**, which run their own nested pumps with **no timer**. WM_ACTIVATEAPP cannot start one because `lpTimerFunc` is still 0.
  4. `lpTimerFunc` is created, the user buttons are set up, `SetMenuEntries`, the cursors are loaded.
  5. `SetTimer(17 ms)`, `LoadAccelerators`, then `GetMessage`/`TranslateAccelerator(rootWnd)`/`TranslateMessage`/`DispatchMessage` until `mainRootWnd==0`.
- **MYTIMERFUNC** (`SIMANT_MODULE:2440`) works like this:
  1. If the main window is iconic, it animates the class icon.
  2. `ticks++` (`0x2EE`).
  3. In the loop, a 32-bit tick counter increments. Network games use ProcessPost/NetworkSend.
  4. When the speed-table delay is ≤ `ticks` and the re-entrancy guard `0x2F4` is 0:
     - `ticks=0`, then **`DoAntSim()`** (its only caller) and `myServiceSong()`;
     - then **`UpdateWindows()`** (its only caller), but only when not iconic and either active or every 8th step (`frame&7`) while inactive.
  5. When active: it expires the ribbon message (`MSClipStart(win_hwnd[0x22])`, obj 0x221F) and calls `UpdateYardMessage()`.
  6. It removes pending WM_TIMERs with PeekMessage and adds them to `ticks` (catch-up).
  7. It **loops inside the callback** until one of these holds: at least 2 extra ticks have been consumed and at least 3 passes have run, or at least 3 ticks have been consumed, or `GetAsyncKeyState(VK_LBUTTON)&1`, or the main window is gone.
- **The game step never runs outside MYTIMERFUNC.** It can run inside nested pumps (`win_Events`, `win_GetEvent`, `myDelay`, `UpdateAllWindows`), because those dispatch WM_TIMER to the callback. So the simulation keeps running under custom dialogs unless they call SetPause or StopSimulation. The `0x2F4` guard prevents nested DoAntSim.

---

## 6. Window slots — VERIFIED from constant call sites, except where marked

These come from constant pushes before calls to `win_Open`, `win_Close`, `win_IsWinOpen`, `win_Swap` and `win_DoProxMenu`, plus the hover table. The IDs are logical window IDs; the slot is `id>>8`.

| ID | opener(s) | purpose / notes |
|---|---|---|
| 0x0000 | OpenEditWindow, MakeEditOpen, NewGame, DoUserButton, DoBookMark | edit (main playfield). Has WM_SIZE, GETMINMAXINFO, scroll and zoom handling; the tool cursor applies here |
| 0x0100 | OpenMapWindow, ProcMapRibbonEvent, YardToMap | map |
| 0x0200 | DoScenario | scenario chooser (captured modal loop) |
| 0x0300 | ShowIntro | intro |
| 0x0400 | EndGameDialog | end of game |
| 0x0500 | OpenInfoWindow | info card |
| 0x0600 | EditScentMenu → win_DoProxMenu | scent popup menu |
| 0x0700, 0x0800, 0x2000 | AntMenu → win_DoProxMenu | ant-action popup menus |
| 0x0900 | DoExpMenu | tool/proximity menu; hovering objects 3–8 opens 0x0C00/0x0F00/0x1000/0x1100/0x0D00/0x0E00 (MAINWNDPROC, `DS:037C`) |
| 0x0A00, 0x0B00 | Edit/Map/RibbonToolsMenu → win_DoProxMenu | tool popup menus |
| 0x0C00–0x1100 | MAINWNDPROC hover | proximity submenus |
| 0x1200 | OpenModeWindow | mode control |
| 0x1300 | OpenCasteWindow | caste control |
| 0x1400 | OpenMiniMapWin | minimap |
| 0x1500 | OpenHistoryWindow | history graphs |
| 0x1700 | DrawCastePopUp | caste popup |
| 0x1800 | ScoreDialog | score |
| 0x1900 | MapToYard, ProcYardRibbonEvent | yard (SC_CLOSE → YardToMap) |
| 0x1A00 | Spider/Lion/YellowDialog, DrawSimPayoff | shared message or picture dialog |
| 0x1C00 | (drawn by DoDebugWin via `win_hwnd[0x1C]`) | debug window; **opener UNKNOWN** |
| 0x1D00 | MagnifyMenu | magnifier |
| 0x1E00 | PictureDialog | picture |
| 0x1F00 | AboutDialog | about box |
| 0x2200 / 0x2300 | WINMAIN binds 0x2200 to ribbonBarWnd; `win_Swap` moves the **same HWND** between them | map-context ribbon (DrawMapData) and yard-context ribbon (DrawYardData, UpdateLayQueenModeDisplay) |
| 0x2400 | DoUserButton | user-button popup at the button rectangle |
| 0x2B00 | GiveLesson (constant pushed) | probably a tutorial window; **UNKNOWN** |

**UNKNOWN:** 0x1600, 0x1B00, 0x2100, and 0x2500–0x2C00. No constant opener exists, so they could only be opened with computed IDs. Deciding this needs the window-resource records, not C.

---

## 7. Paint path — VERIFIED

- **BeginPaint runs in only two places:**
  - MAINWNDPROC `2D01`, for the ribbon while `win_handles[0x22]` and `win_handles[0x23]` are both NULL. It fills with GRAY_BRUSH and centres "This is the ribbon bar.".
  - `PaintStuff` (`GR_MODULE:3E92`, admitted), for every hwnd that is not mainRootWnd or rootWnd, is visible, and has an INDEX. PaintStuff copies the update region into `updateRgn` (`GetUpdateRgn`), calls `BeginPaint`, selects and realizes `paletteH`, `GSetBigFont`, `win_DrawWindow(INDEX)`, then `EndPaint` and deletes the region.
  - mainRootWnd (INDEX −1) and rootWnd (no INDEX, filtered out in PaintStuff) go to DefWindowProc.
- **Erasing:** WM_ERASEBKGND is not handled, so DefWindowProc erases with the class brush: GenericWindow white (COLOR_WINDOW), AntRoot APPWORKSPACE, Ribbon LTGRAY.
  - Erasing invalidations (`TRUE`): `win_Open`, `win_Swap`, and the ribbon on WM_SIZE, followed by a synchronous UpdateWindow.
  - Non-erasing invalidations (`FALSE`): palette refreshes (MYENUMFUNC and the ribbon).
- **Direct draw:** `MSClipStart(hwnd)` (`GR_MODULE:3DFA`) does `GetDC(hwnd)`, sets `clipWind`/`clipDC`, sets `updateRgn=0` (no update-region clipping), selects and realizes the palette and sets the font. `MSClipEnd` restores and calls `ReleaseDC`.
  - It is used outside WM_PAINT by MYTIMERFUNC (ribbon message), UpdateWindows, MAINWNDPROC (map cursor on WM_SIZE, hover inversion), the Goto*/scroll routines, the dialogs, the menus, and the xref list in `all.asm`.
  - This is immediate GDI output to the window DC.
- **Coordinates are window-local.** Nothing calls SetViewportOrg, SetWindowOrg, OffsetRect or OffsetRgn. `SetMapMode` appears only in GPutStr. Hit tests convert to the target's client coordinates before comparing with object rectangles: `win_GetEvent` uses `GetCursorPos` then `ScreenToClient(target)`; MAINWNDPROC mousemove uses `ScreenToClient(hit)`; DoMouse uses the lParam client point.
- **Edges:** `PointInRect` (`GR_MODULE:497A`) is inclusive (`left<=x<=right`, `top<=y<=bottom`) when `ribbonBarHeight==0`, which is always the case in retail (§3). The half-open branch is dead.

---

## Corrections to the section drafts (the original code contradicts them)

1. **p1 §B line 12 and Q8** ("never sets WS_CHILD", "owned top-level"): wrong. `win_Open` always ORs `0x44000000` (WS_CHILD\|WS_CLIPSIBLINGS) at `CD1A`, with parent rootWnd. All logical windows are **child windows of rootWnd**, so every "overlapped top-level / owner rootWnd" cell in the inventory is wrong.
2. **p1 Q2 and inventory row 0x2300:** 0x2300 has no HWND of its own. `win_Swap` moves ribbonBarWnd and its INDEX between 0x2200 and 0x2300 on the WM_NCACTIVATE of the edit and yard windows.
3. **p1 Q7:** 0x1F00 is opened by `AboutDialog`.
4. **p1 Q5, p2 line 37 and p3:** INDIRECTDLGPROC is at `DDD2` (p2 says `DDA2`) and has **no reference in code**. It is not a live dialog path, so no native modal dialogs need SDL windows apart from COMMDLG and the Open/Save `DialogBox` fallback.
5. **p2 REPORT and line 34** ("WINMAIN gives SetTimer a StopSimulation thunk", "RestartSimulation null callback", "non-root timer 0xAA calls StopSong"): wrong.
   - The callback is MYTIMERFUNC (the `StopSimulation` name is the segment-base fixup).
   - RestartSimulation passes `lpTimerFunc`.
   - `0xAA` is the 170 ms background interval set on WM_ACTIVATEAPP(FALSE), where StopSong is called directly.
   - p4 already fixed the equivalent MYENUMFUNC misreading.
6. **p2 line 13** (MYTIMERFUNC "reached on the root WM_TIMER path"): USER calls it directly as the timer callback. The MAINWNDPROC WM_TIMER branch is dead in practice.
7. **p2 line 25:** WM_KEYUP is not handled; it goes to DefWindowProc. There is no UpdateEdit on key-up. `UpdateEditIfBufInvalid` runs on WM_MOVE, WM_SIZE, WM_CLOSE and WM_NCACTIVATE.
8. **p2 lines 32–33:** the special command IDs are `0xFDA0–0xFDAC`, not `0x00A0–0x00AC`. `0xF9xx` belongs to WM_COMMAND (the popUpMenuId store), not WM_SYSCOMMAND. `0xFDA1` is SC_KEYMENU (opens the system menu), not minimize.
9. **p2 line 23:** DoMouse calls DoEvent only for down and double-click messages. Up messages only update `mouse_state`. Double-clicks on object types 5, 0x0D and 0x11 are dropped.
10. **p3 line 26 and REPORT Q2** ("captures on WM_LBUTTONDOWN, releases after WM_RBUTTONUP"): wrong. MAINWNDPROC takes and releases capture only in the paths listed in §2.
11. **p3 REPORT Q1 and p1 Q4 (auto-close UNKNOWN):** now settled, see §4. Win16 closes on any left-down delivered to the top bit-0 window.
12. **p5 line 21** ("for rootWnd, AdjustWndMinMax"): AdjustWndMinMax is called for `win_hwnd[0]` (the edit window). For rootWnd, WM_GETMINMAXINFO goes to DefWindowProc.
13. **p5 line 13, p1 Q3, p4 "coordinate origin" UNKNOWN:** the `ribbonBarHeight` subtraction is a no-op in retail because the variable is always 0. Rectangles are rootWnd-client coordinates, object rectangles are window-client-local, and `PointInRect` is inclusive.
14. **p2 line 28 / p4 REPORT (no WM_SETFOCUS, KILLFOCUS or ERASEBKGND case):** now VERIFIED from the dispatch tree, and upgraded from inferred. Focus is set only by `SetFocus(rootWnd)` on app activation, so key messages arrive with `hwnd=rootWnd`.

## What still needs data, not C

- Window-record flags (`+0x1C` bits 0/4/8/0x10/0x40/0x80, `+0x1D` bit 0) and their rectangles for each slot. These determine the style, whether a window auto-closes, and whether it is modal. They are in the window resource loaded by `win_LoadAllWindows`, so a record decode (about a day) settles them.
- The purposes of 0x1600, 0x1B00, 0x2100, 0x2500–0x2C00 and 0x2B00 (the same decode, plus the computed-ID callers).
- **No exact C reconstruction is needed for any answer here.** Every branch above was read directly from the original instructions.
