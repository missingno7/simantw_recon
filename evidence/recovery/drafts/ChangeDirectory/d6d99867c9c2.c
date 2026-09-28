/*
 * Read and validate the directory edit control, normalize the path prefix,
 * and refresh the directory list box.  The two Dx8-based buffers are kept
 * as views of the selector-backed storage named by the packet.
 */
extern int far pascal GetDlgItemText(int window, int control,
                                     char far *text, int count);
extern long far pascal SendDlgItemMessage(int window, int control,
                                          int message, int wParam,
                                          long lParam);
extern int far pascal lstrlen(char far *text);
extern char far * far pascal AnsiPrev(char far *start, char far *current);
extern char far * far pascal lstrcpy(char far *dest, char far *source);
extern char far *strcat(char far *dest, const char far *source);
extern char far * far strchr(char far *text, int value);
extern int UpdateListBox(int window, int mode);
extern char __based(__segname("SIMANT_DATA_GROUP")) Dx8[];

#define DX8PTR(offset) ((char far *)(char __based(__segname("SIMANT_DATA_GROUP")) *)(unsigned)(offset))

int far ChangeDirectory(int windowArg, char far *path, int mode)
{
    char scratch[256];
    char far *previous;
    char saved;
    register int windowCopy;
    windowCopy = windowArg;
    GetDlgItemText(windowCopy, 0x191, path, 0x80);
    path[0x7f] = 0;

    if (strchr(path, '*') || strchr(path, '?'))
        return 0;

    if (mode == 0xc010) {
        SendDlgItemMessage(windowCopy, 0x194, 0x0409, 0, 0L);
        return 0;
    }

    previous = path + lstrlen(path);
    if (*previous != ':' && *previous != '\\' && previous > path)
        previous = AnsiPrev(path, previous);

    if (*previous == ':' || *previous == '\\') {
        lstrcpy(DX8PTR(0x9f10), previous + 1);
        saved = *(previous + 1);
        lstrcpy(scratch, path);
        *(previous + 1) = saved;
        scratch[(unsigned)(previous + 1 - path) + 1] = 0;
    } else {
        lstrcpy(DX8PTR(0x9f10), path);
        scratch[0] = 0;
    }

    if (scratch[0])
        strcat(scratch, DX8PTR(0x94a0));

    UpdateListBox(windowCopy, mode);
    return 1;
}
