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
extern char far * far strchr(char far *text, int value);
extern int UpdateListBox(int window, int mode);
extern char far Dx8[];

int far ChangeDirectory(int window, char far *path, int mode)
{
    char scratch[256];
    char far *work;
    char far *end;
    char far *previous;
    char saved;
    int winCopy = window; char far *pathCopy = path;

    GetDlgItemText(winCopy, 0x191, pathCopy, 0x80);
    pathCopy[0x7f] = 0;

    if (strchr(pathCopy, '*') || strchr(pathCopy, '?'))
        return 0;

    if (mode == 0xc010) {
        SendDlgItemMessage(winCopy, 0x194, 0x0409, 0, 0L);
        return 0;
    }

    work = (char far *)Dx8 + 0x9f10;
    end = pathCopy + lstrlen(pathCopy);
    if (*end != ':' && *end != '\\' && end > pathCopy) {
        previous = AnsiPrev(pathCopy, end);
        if (*previous != ':' && *previous != '\\')
            lstrcpy(work, pathCopy);
        else
            lstrcpy(work, previous + 1);
    } else {
        lstrcpy(work, pathCopy);
    }

    scratch[0] = 0;
    saved = *end;
    lstrcpy(scratch, pathCopy);
    *end = saved;
    scratch[(unsigned)(end - pathCopy) + 1] = 0;

    if (scratch[0]) {
        unsigned int i;
        unsigned int length;
        char far *destination;

        length = 0;
        while (scratch[length])
            ++length;
        destination = (char far *)Dx8 + 0x94a0;
        for (i = 0; i <= length; ++i)
            destination[i] = scratch[i];
    }

    UpdateListBox(winCopy, mode);
    return 1;
}
