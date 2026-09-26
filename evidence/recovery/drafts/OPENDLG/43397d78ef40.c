/* Round 13d: clear the stored directory when the selected name has no prefix. */
/* Round 10a: same-segment C call with source-order dialog and mode. */
/* Round 4: distinct branch and local-layout hypothesis. */
/*
 * OPENDLG is the dialog procedure for the open-file UI.  The four branches
 * below are grounded in the WM_INITDIALOG/WM_COMMAND values and the controls
 * visible in the packet; `dialog` is the selector-sized dialog handle passed
 * in the final stack word.  The first argument is retained because it occupies
 * a stack word even though this routine does not read it.
 */
extern int near UpdateListBox(int dialog, int mode);
extern int far pascal SetDlgItemText(int dialog, int item, char far *text);
extern int far pascal SendDlgItemMessage(int dialog, int item, int message,
                                         int wParam, long lParam);
extern int far pascal GetDlgItem(int dialog, int item);
extern int far pascal SetFocus(int window);
extern int far pascal EndDialog(int dialog, int result);
extern int far pascal GetWindowText(int window, char far *text, int count);
extern int far pascal MessageBox(int window, char far *text,
                                 char far *caption, int type);
extern int far pascal lstrlen(char far *text);
extern char far * far pascal lstrcpy(char far *dest, char far *source);
extern char far * far pascal AnsiPrev(char far *start, char far *current);
extern char far * far pascal strchr(char far *text, int value);
extern unsigned char far Dx8[];

int far pascal OPENDLG(int dialog, int message, int item, int mode, int unused)
{
    char path[0x106];
    char prefix[0x100];
    char far *end;
    char far *last;
    int length;
    int result;

    switch (message) {
    case 0x110: {
        UpdateListBox(dialog, 0x4010);
        SetDlgItemText(dialog, 0x191, (char far *)(Dx8 + 0x9f10));
        SendDlgItemMessage(dialog, 0x191, 0x0401, 0, 0x7fffL);
        SetFocus(GetDlgItem(dialog, 0x191));
        return 0;
    }
    case 0x111:
        break;
    default:
        return 0;
    }

    if (item == 2) {
        EndDialog(dialog, 0);
        return 0;
    }

    if (item != 0x194)
        return 0;

    if (mode != 2) {
        if (mode != 1)
            return 0;
        GetWindowText(dialog, path, 0x194);
        if (strchr(path, '*') != 0 || strchr(path, '?') != 0)
            return 0;

        length = lstrlen(path);
        end = path + length;
        last = end;
        if (*end != ':' && *end != '\\' && end > path)
            last = AnsiPrev(path, end);

        prefix[0] = 0;
        if (*last == ':' || *last == '\\') {
            lstrcpy((char far *)(Dx8 + 0x9f10), last + 1);
            length = (int)(last + 1 - path);
            while (length-- > 0)
                prefix[length] = path[length];
            prefix[(int)(last + 1 - path)] = 0;
        } else {
            lstrcpy((char far *)(Dx8 + 0x9f10), path);
        }

        if (prefix[0])
            lstrcpy((char far *)(Dx8 + 0x94a0), prefix);
        else
            ((char far *)(Dx8 + 0x94a0))[0] = 0;
        UpdateListBox(dialog, 0x4010);
        result = 1;
        return result;
    }

    if (mode == 2) {
        GetWindowText(dialog, path, 0x194);
        if (path[0] == 0)
            MessageBox(dialog, (char far *)(Dx8 + 0x16cf), 0, 0x10);
        else
            SetFocus(dialog);
        return 0;
    }

    return 0;
}
