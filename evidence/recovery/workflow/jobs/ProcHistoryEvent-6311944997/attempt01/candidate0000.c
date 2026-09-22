/*
 * ProcHistoryEvent: dispatches the history window's (simant:8A76) control
 * events.  event->message (offset 0xc of the far event struct, same
 * reserved[12]+message shape as the admitted ProcEditEvent) selects one
 * of three actions: 0x150d shows history help (DoWinHelp(0x150f)); 0x150e
 * redraws the history graph object (0x150e) twice -- once per colony slot
 * (Dx8[0x8e54..0x8e5c), 4 words, sentinel 0x8000 = empty) with flag 1
 * while clipped to win_hwnd[21] (0xbcd0, the same unnamed near word
 * ToggleHistButton also binds), then again with flag 0 after the mouse
 * button is released (StillDown()); the 0x1503..0x150c range (matching
 * ToggleHistButton's own button ids) forwards the raw message to
 * ToggleHistButton. Every other message is ignored.
 */
struct HistEvent {
    char reserved[12];
    int message;
};

extern int near win_hwnd[];
extern unsigned char far Dx8[];

extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void far DoWinHelp(int mode);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern int far StillDown(void);
extern void far drawHistGraph(int value, int flag, int index);
extern void far ToggleHistButton(int message);

void far ProcHistoryEvent(struct HistEvent far *event)
{
    int message;
    int v1;
    int v2;
    unsigned int p;
    int i;

    message = event->message;

    if (message == 0x150d) {
        DoWinHelp(0x150f);
        return;
    }

    if (message == 0x150e) {
        clip_SetWin(0x1500);
        MSClipStart(win_hwnd[21]);
        win_FillObjRect(0x150e, ConvColor(0));
        for (i = 0, p = 0x8e54; p < 0x8e5c; p += 2, i++) {
            v1 = *(int far *)&Dx8[p];
            if (v1 != (int)0x8000)
                drawHistGraph(v1, 1, i);
        }
        while (StillDown())
            ;
        win_FillObjRect(0x150e, ConvColor(0));
        for (i = 0, p = 0x8e54; p < 0x8e5c; p += 2, i++) {
            v2 = *(int far *)&Dx8[p];
            if (v2 != (int)0x8000)
                drawHistGraph(v2, 0, i);
        }
        clip_Off();
        MSClipEnd();
        return;
    }

    if (event->message >= 0x1503 && event->message <= 0x150c)
        ToggleHistButton(message);
}
