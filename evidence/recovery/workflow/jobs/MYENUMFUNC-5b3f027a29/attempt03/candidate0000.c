/*
 * This is a window-enumeration callback.  The first argument identifies the
 * window currently being considered and the third is the window to refresh.
 * Equal handles, or a hidden refresh target, take the common TRUE return
 * path; visible non-equal targets are invalidated before returning TRUE.
 */
extern int far pascal IsWindowVisible(int window);
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);

int far pascal __loadds MYENUMFUNC(int target, int unused, int window)
{
    if (window != target && IsWindowVisible(target))
        InvalidateRect(target, (void far *)0, 0);
    return 1;
}
