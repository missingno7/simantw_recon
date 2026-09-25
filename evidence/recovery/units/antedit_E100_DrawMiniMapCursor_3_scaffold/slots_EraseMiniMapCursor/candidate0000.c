struct MiniMapRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near win_hwnd[];
extern struct MiniMapRect far miniMapCursorRect;
extern int near mmapCursorState;
extern void far MSClipStart(int window);
extern void far GRectInvOutline(struct MiniMapRect far *rect, int color);
extern void far MSClipEnd(void);

void EraseMiniMapCursor(void)
{
    MSClipStart(win_hwnd[20]);
    GRectInvOutline(&miniMapCursorRect, 1);
    MSClipEnd();
    mmapCursorState = 0;
}
