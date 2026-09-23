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
    GetDlgItemText(window, 0x191, path, 0x80);
    path[0x7f] = 0;

    if (strchr(path, '*') || strchr(path, '?'))
        return 0;

    if (mode == 0xc010) {
        SendDlgItemMessage(window, 0x194, 0x0409, 0, 0L);
        return 0;
    }

    work = (char far *)Dx8 + 0x9f10;
    end = path + lstrlen(path);
    previous = end;
    if (*end != ':' && *end != '\\' && end > path)
        previous = AnsiPrev(path, end);

    if (*previous == ':' || *previous == '\\') {
        lstrcpy(work, previous + 1);
        saved = *(previous + 1);
        lstrcpy(scratch, path);
        *(previous + 1) = saved;
        scratch[(unsigned)(previous + 1 - path) + 1] = 0;
    } else {
        lstrcpy(work, path);
        scratch[0] = 0;
    }

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

    UpdateListBox(window, mode);
    return 1;
}
