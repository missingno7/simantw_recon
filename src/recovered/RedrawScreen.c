extern int near rootWnd;
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);
extern void far pascal UpdateWindow(int window);

void RedrawScreen(void)
{
    InvalidateRect(rootWnd, (void far *)0, 1);
    UpdateWindow(rootWnd);
}
