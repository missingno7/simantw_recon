/*
 * Hypothesis: repeatedly remove pending Windows messages from the three
 * event ranges used by the application.  The local is the 18-byte Win16
 * MSG structure; PeekMessage is the USER ordinal-109 Pascal import shown in
 * the packet, so the compiler emits the observed left-to-right pushes.
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

void far win_FlushEvents(void)
{
    struct MSG message;

    while (PeekMessage(&message, 0, 0x200, 0x209, 1) ||
           PeekMessage(&message, 0, 0x100, 0x108, 1) ||
           PeekMessage(&message, 0, 0x21, 0x21, 1)) {
    }
}
