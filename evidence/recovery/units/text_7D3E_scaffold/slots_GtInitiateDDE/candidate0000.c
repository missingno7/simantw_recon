/* Create the client window and broadcast its DDE initiation request. */
extern char near commandStr[];
extern unsigned int far pascal CreateWindow(char far *class_name,
                                            char far *window_name,
                                            unsigned int style,
                                            int x, int y, int width, int height,
                                            unsigned int parent,
                                            unsigned int menu,
                                            unsigned int instance,
                                            void far *parameter);
extern unsigned int far pascal GlobalAddAtom(char far *name);
extern unsigned int far pascal GlobalDeleteAtom(unsigned int atom);
extern long far pascal SendMessage(unsigned int hwnd, unsigned int message,
                                   unsigned int wParam, long lParam);
extern int far pascal DestroyWindow(unsigned int hwnd);
extern int far cdecl wsprintf(char far *buffer, char far *format, ...);
extern void far DebugWinPrintf(char far *format, ...);

int far GtInitiateDDE(unsigned int parent, unsigned int instance)
{
    char buffer[256];
    unsigned int window;
    unsigned int app_atom;
    unsigned int topic_atom;
    long atom_pair;

    if (*(unsigned int near *)(commandStr + 0x50) != 0)
        return 1;

    window = CreateWindow((char far *)(commandStr + 0x1a3),
                          (char far *)(commandStr + 0x199),
                          0x4000, 0, 0, 0, 0, parent, 0, instance, 0);
    *(unsigned int near *)(commandStr + 0x50) = window;
    wsprintf((char far *)buffer, (char far *)(commandStr + 0x1b2), window);
    DebugWinPrintf((char far *)buffer);

    if (*(unsigned int near *)(commandStr + 0x50) == 0) {
        DestroyWindow(*(unsigned int near *)(commandStr + 0x50));
        *(unsigned int near *)(commandStr + 0x50) = 0;
        return 0;
    }

    app_atom = GlobalAddAtom((char far *)(commandStr + 0x1c9));
    topic_atom = GlobalAddAtom((char far *)(commandStr + 0x1cf));
    *(unsigned int near *)(commandStr + 0x4c) = 1;
    atom_pair = ((unsigned long)topic_atom << 16) | app_atom;
    SendMessage(0xffff, 0x3e0,
                *(unsigned int near *)(commandStr + 0x50), atom_pair);
    *(unsigned int near *)(commandStr + 0x4c) = 0;
    GlobalDeleteAtom(app_atom);
    GlobalDeleteAtom(topic_atom);

    if (*(unsigned int near *)(commandStr + 0x4e) != 0)
        return 1;
    DestroyWindow(*(unsigned int near *)(commandStr + 0x50));
    *(unsigned int near *)(commandStr + 0x50) = 0;
    return 0;
}
