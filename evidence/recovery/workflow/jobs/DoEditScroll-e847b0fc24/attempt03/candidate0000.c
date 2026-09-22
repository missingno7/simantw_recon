/*
 * DoEditScroll: WM_HSCROLL/WM_VSCROLL handler for the edit window's own
 * scroll bars.  message selects the bar (0x114 = WM_HSCROLL, else
 * WM_VSCROLL); code is the low word of wParam (SB_LINEUP=0, SB_LINEDOWN=1,
 * SB_PAGEUP=2, SB_PAGEDOWN=3, SB_THUMBPOSITION=4, SB_THUMBTRACK=5,
 * SB_TOP=6, SB_BOTTOM=7 -- 4 and 5 share one body); pos is the thumb
 * position for 4/5.  GetScrollRange(hwnd, bar, &min, &max) is fetched once
 * up front for whichever bar this call concerns.  MapPnt.x/y hold the
 * current horizontal/vertical scroll offsets.  LINEUP/LINEDOWN try a cheap
 * incremental redraw (EditScrollLeftAsm/RightAsm/UpAsm/DownAsm) when the
 * edit window is in front and exposed, tracked by scrolled, and fall back
 * to DoEditScrollLine (recording the change without a screen update) when
 * it is not; PAGEUP/PAGEDOWN/TOP/BOTTOM always request the final redraw.
 * THUMBPOSITION/TRACK are gated by an unnamed far flag (dx8Flag) sharing
 * Dx8's segment: when it (or an outright THUMBPOSITION) applies, MapPnt is
 * set to pos and only THUMBPOSITION also repositions the thumb itself.
 */
struct Point {
    int x;
    int y;
};

extern int near editWidth;
extern int near editHeight;
extern int near scrollBarFlag;
extern struct Point far mapPntPoint;
extern int far editBufInvalidFlag;
extern int far TutLesson;
extern int far LessonTemp;
extern int far match_position[];
extern unsigned char far Dx8[];
extern int far dx8ThumbFlag;
extern int near win_hwnd[];
extern int near editDeltaBounds[4];

extern void far pascal GetScrollRange(int hwnd, int bar, int far *lo, int far *hi);
extern void far pascal SetScrollPos(int hwnd, int bar, int pos, int redraw);
extern int far win_IsWinInFront(int window);
extern int far win_IsWinExposed(int window);
extern void far EditScrollLeftAsm(int p0, int p1, int p2, int p3, int height, int width);
extern void far EditScrollRightAsm(int p0, int p1, int p2, int p3, int height, int width);
extern void far EditScrollUpAsm(int p0, int p1, int p2, int p3, int height, int width);
extern void far EditScrollDownAsm(int p0, int p1, int p2, int p3, int height, int width);
extern void far DoEditScrollLine(int code);
extern void far UpdateEdit(void);
extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far EraseMapCursor(void);
extern void far DrawMapCursor(void);
extern void far MSClipEnd(void);

void far DoEditScroll(int hwnd, int message, int code, int pos)
{
    int scrolled;
    int lo;
    int hi;

    scrolled = 0;
    if (message == 0x114)
        GetScrollRange(hwnd, 0, &lo, &hi);
    else
        GetScrollRange(hwnd, 1, &lo, &hi);

    switch (code) {
    case 0: /* SB_LINEUP */
        if (message == 0x114) {
            if (mapPntPoint.x <= lo) {
                /* nothing to scroll */
            } else {
                SetScrollPos(hwnd, 0, --mapPntPoint.x, 1);
                if (win_IsWinInFront(0) && win_IsWinExposed(0)) {
                    editBufInvalidFlag = 1;
                    EditScrollLeftAsm(editDeltaBounds[0], editDeltaBounds[1], editDeltaBounds[2], editDeltaBounds[3], editHeight, editWidth);
                    scrolled = 1;
                    scrollBarFlag = scrolled;
                } else {
                    DoEditScrollLine(0x6c);
                    scrolled = 0;
                }
            }
        } else {
            scrolled = 0;
            if (mapPntPoint.y > hi) {
                SetScrollPos(hwnd, 1, --mapPntPoint.y, 1);
                scrolled = 1;
                if (win_IsWinInFront(0) && win_IsWinExposed(0)) {
                    editBufInvalidFlag = scrolled;
                    EditScrollUpAsm(editDeltaBounds[0], editDeltaBounds[1], editDeltaBounds[2], editDeltaBounds[3], editHeight, editWidth);
                    scrollBarFlag = scrolled;
                } else {
                    DoEditScrollLine(0x75);
                }
            }
        }
        break;
    case 1: /* SB_LINEDOWN */
        if (message == 0x114) {
            if (mapPntPoint.x >= hi) {
                break;
            }
            SetScrollPos(hwnd, 0, ++mapPntPoint.x, 1);
            scrolled = 1;
            if (win_IsWinInFront(0) && win_IsWinExposed(0)) {
                editBufInvalidFlag = scrolled;
                EditScrollRightAsm(editDeltaBounds[0], editDeltaBounds[1], editDeltaBounds[2], editDeltaBounds[3], editHeight, editWidth);
                scrollBarFlag = scrolled;
            } else {
                DoEditScrollLine(0x72);
            }
        } else {
            if (mapPntPoint.y >= hi) {
                break;
            }
            SetScrollPos(hwnd, 1, ++mapPntPoint.y, 1);
            scrolled = 1;
            if (win_IsWinInFront(0) && win_IsWinExposed(0)) {
                editBufInvalidFlag = scrolled;
                EditScrollDownAsm(editDeltaBounds[0], editDeltaBounds[1], editDeltaBounds[2], editDeltaBounds[3], editHeight, editWidth);
                scrollBarFlag = scrolled;
            } else {
                DoEditScrollLine(0x64);
            }
        }
        break;
    case 2: /* SB_PAGEUP */
        if (message == 0x114) {
            mapPntPoint.x -= editWidth;
            if (mapPntPoint.x < lo)
                mapPntPoint.x = lo;
            SetScrollPos(hwnd, 0, mapPntPoint.x, 1);
        } else {
            mapPntPoint.y -= editHeight;
            if (mapPntPoint.y < lo)
                mapPntPoint.y = lo;
            SetScrollPos(hwnd, 1, mapPntPoint.y, 1);
        }
        scrolled = 1;
        break;
    case 3: /* SB_PAGEDOWN */
        if (message == 0x114) {
            mapPntPoint.x += editWidth;
            if (mapPntPoint.x > hi)
                mapPntPoint.x = hi;
            SetScrollPos(hwnd, 0, mapPntPoint.x, 1);
        } else {
            mapPntPoint.y += editHeight;
            if (mapPntPoint.y > hi)
                mapPntPoint.y = hi;
            SetScrollPos(hwnd, 1, mapPntPoint.y, 1);
        }
        scrolled = 1;
        break;
    case 4: /* SB_THUMBPOSITION */
    case 5: /* SB_THUMBTRACK */
        if (dx8ThumbFlag != 0 || code == 4) {
            if (message == 0x114) {
                scrolled = (mapPntPoint.x != pos);
                mapPntPoint.x = pos;
                if (code == 4)
                    SetScrollPos(hwnd, 0, mapPntPoint.x, 1);
            } else {
                scrolled = (mapPntPoint.y != pos);
                mapPntPoint.y = pos;
                if (code == 4)
                    SetScrollPos(hwnd, 1, mapPntPoint.y, 1);
            }
        } else {
            scrolled = 0;
        }
        break;
    case 6: /* SB_TOP */
        mapPntPoint.x = lo;
        mapPntPoint.y = lo;
        SetScrollPos(hwnd, 1, lo, 1);
        SetScrollPos(hwnd, 0, mapPntPoint.x, 1);
        scrolled = 1;
        break;
    case 7: /* SB_BOTTOM */
        mapPntPoint.x = hi;
        mapPntPoint.y = hi;
        SetScrollPos(hwnd, 1, hi, 1);
        SetScrollPos(hwnd, 0, mapPntPoint.x, 1);
        scrolled = 1;
        break;
    }

    if (scrolled) {
        UpdateEdit();
        if (win_IsWinOpen(0x100)) {
            MSClipStart(win_hwnd[1]);
            EraseMapCursor();
            DrawMapCursor();
            MSClipEnd();
        }
    }
    scrollBarFlag = 0;
    if (TutLesson == 0x32)
        LessonTemp = 1;
}
