# _DoKeyDown first-pass evidence

Job: `DoKeyDown-785609ef21`, assigned MSC 7.00 baseline profile. One candidate was strict-tested and did not match; no further candidate was tried.

## Established call contract

`MAINWNDPROC` dispatches the four words to `_DoKeyDown` by pushing its `lParam` high and low words, `wParam`, then `hwnd`. At `_DoKeyDown` entry the corresponding parameters are `[bp+6]=hwnd`, `[bp+8]=virtual key`, `[bp+0xa]=lParam low`, `[bp+0xc]=lParam high`. The high word is tested against `0x4000`, the WM_KEYDOWN previous-state bit. The admitted `_HelpKeyDown` reads hwnd/key and directly documents F1 with Shift toggling `bHelp`, F1 without Shift calling WinHelp index, Escape leaving help mode, and Delete toggling help mode.

Pinned `sdk300/WLIB/LIBW.LIB` import evidence maps USER.17 to `GetCursorPos`, USER.25 to `GetProp`, USER.29 to `ScreenToClient`, USER.70 to `SetCursorPos`, USER.106 to `GetKeyState`, USER.109 to `PeekMessage`, USER.249 to `GetAsyncKeyState`, and KEYBOARD.131 to `MapVirtualKey`.

Original DGROUP bytes show the property string `INDEX` at 0x1de and three adjacent debug formats at 0x1e4, 0x201, and 0x224 (`DoKeyDown: Flash(start)`, `Flash(almost done)`, and `Flash(done)`). The handler resets words at 0x1da and 0x1dc on Enter; a circular four-byte key buffer is indexed through DS:0xCC3A..0xCC3D and compared against complemented four-byte entries at `Dx8:0x83bc`, with a matching entry passed to `CheatKeys`.

## Still unresolved

The strict-tested candidate simplified the Insert/Space selection path. Although the disassembly directly shows `win_FindObject`, an object pointer, flag tests at offsets 0x24/0x25, `win_SetGroupSelectedObj`, `win_SetObjSelectedState`, and three `WinPrintf` calls around `WaitHundredths(5)`, it does not establish the source-level group/selection argument meanings or all conditional state transitions. The candidate also guessed fields/state in the 16-byte `DoEvent` record after a filtered `PeekMessage`; those assignments and the exact `mouse_state` encoding need a source-level derivation from the complete target/call path.

The first candidate is preserved at `candidate.c`; its strict report is `attempt01/results.json`. Result: `NO_COMPLETE_MATCH`, target 1,385 bytes, candidate 989 bytes, 89/514 opcodes, 1/58 fixups, score 0.121595. The report also flags conflicting private `_DATA` and `_BSS` placement, so no acceptance is possible from this candidate.
