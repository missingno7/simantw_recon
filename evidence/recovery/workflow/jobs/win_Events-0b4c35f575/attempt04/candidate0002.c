/*
 * win_Events: drain the Windows message queue and report whether a
 * "user acted" event was seen.  The local is the 18-byte Win16 MSG
 * structure; PeekMessage (USER ordinal 109), TranslateMessage (113) and
 * DispatchMessage (114) are the Pascal imports shown in the packet.  While
 * PeekMessage(&msg, 0, 0, 0, PM_REMOVE) returns a message: a left-button
 * down or up (0x201/0x202) sets the result, as does a WM_KEYDOWN (0x100)
 * for space (0x20) or insert (0x2d); every message is then translated and
 * dispatched.  The result flag lives in SI, which is why the first
 * PeekMessage pushes the zero arguments from SI and the rotated loop test
 * pushes literal zeros.
 */
struct MSG {
    int hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    int pt_x;
    int pt_y;
};

extern int far pascal PeekMessage(struct MSG far *message,
                                  int hwnd, unsigned int first,
                                  unsigned int last, unsigned int remove);
extern int far pascal TranslateMessage(struct MSG far *message);
extern long far pascal DispatchMessage(struct MSG far *message);

int far win_Events(void)
{
    struct MSG msg;
    int acted;

    acted = 0;
    while (PeekMessage(&msg, acted, acted, acted, 1)) {
        if (msg.message == 0x201 || msg.message == 0x202)
            acted = 1;
        if (msg.message == 0x100 &&
            (msg.wParam == 0x20 || msg.wParam == 0x2d))
            acted = 1;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return acted;
}

