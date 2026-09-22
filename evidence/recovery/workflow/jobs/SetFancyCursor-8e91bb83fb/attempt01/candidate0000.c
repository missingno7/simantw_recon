/*
 * SetFancyCursor: set the mouse cursor to the current tool's icon while
 * Shift is held over the map or yard window. Reached only when the given
 * window is the map window (win_hwnd[0]) and it is the front window (via
 * win_IsWinInFront(0)), or the window is the yard window (win_hwnd[1])
 * and it is the front window (via win_IsWinInFront(0x100)) -- the two
 * clauses of one "||" of "&&"s. Inside that, Shift must be held
 * (GetAsyncKeyState(VK_SHIFT) high bit), button must equal 1 and
 * CurGameType (MAPSYM 0x80b4, its own selector) must equal 3 (playing).
 * CurExpTool (MAPSYM 0x79e2, its own selector) then selects one of the
 * seven cursors loaded by LoadFancyCursor through a dense switch (the
 * same cmp/ja/shl/xchg/jmp cs:[bx+T] idiom as the admitted
 * DoUserButtonUpdate); an out-of-range tool shares the same "return 1"
 * tail without a SetCursor call. Any failed guard returns 0.
 */
extern int near win_hwnd[];
extern int far win_IsWinInFront(int window);
extern int far pascal GetAsyncKeyState(int key);
extern unsigned int far pascal SetCursor(unsigned int cursor);
extern int far CurGameType;
extern int far CurExpTool;
extern unsigned int near magCursor;
extern unsigned int near rockCursor;
extern unsigned int near digCursor;
extern unsigned int near antCursor;
extern unsigned int near foodCursor;
extern unsigned int near dropCursor;
extern unsigned int near sprayCursor;

int far SetFancyCursor(int window, int button)
{
    if ((window == win_hwnd[0] && win_IsWinInFront(0)) ||
        (window == win_hwnd[1] && win_IsWinInFront(0x100))) {
        if ((GetAsyncKeyState(0x10) & 0x8000) && button == 1 && CurGameType == 3) {
            switch (CurExpTool) {
            case 0:
                SetCursor(magCursor);
                break;
            case 1:
                SetCursor(rockCursor);
                break;
            case 2:
                SetCursor(digCursor);
                break;
            case 3:
                SetCursor(antCursor);
                break;
            case 4:
                SetCursor(foodCursor);
                break;
            case 5:
                SetCursor(dropCursor);
                break;
            case 6:
                SetCursor(sprayCursor);
                break;
            }
            return 1;
        }
    }
    return 0;
}
