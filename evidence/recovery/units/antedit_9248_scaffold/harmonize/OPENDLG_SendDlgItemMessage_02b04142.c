/* Round 32b: dispatch the command item through a target-shaped switch. */
/* Round 30b: copy mode-one text through the target selector with a byte loop. */
/* Round 24a: pass the Dx8 selector-backed string directly at each far call. */
/* Round 20c: recover the global selector-buffer mode-two path handler. */
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
extern long far pascal SendDlgItemMessage(int dialog, unsigned item,
                                           unsigned message, unsigned wParam,
                                           unsigned long lParam);
extern int far pascal GetDlgItem(int dialog, int item);
extern int far pascal SetFocus(int window);
extern int far pascal EndDialog(int dialog, int result);
extern int far pascal DlgDirSelect(int window, char far *text, int count);
extern int far pascal GetDlgItemText(int dialog, int item, char far *text, int count);
extern int far pascal MessageBox(int window, char far *text,
                                 char far *caption, int type);
extern unsigned int far strlen(char far *text);
extern char far * far strcpy(char far *dest, char far *source);
extern char far * far strcat(char far *dest, char far *source);
extern char far *strncpy(char far *dest, char far *source, unsigned int count);
extern char far * far pascal AnsiPrev(char far *start, char far *current);
extern char far * far strchr(char far *text, int value);
extern unsigned char far Dx8[];

int far pascal OPENDLG(int dialog, int message, int item, int mode, int unused)
{
    char prefix[0x100];
    char path[0x106];
    char far *last;

    switch (message) {
    case 0x110: {
        UpdateListBox(dialog, 0x4010);
        SetDlgItemText(dialog, 0x191, (char far *)(Dx8 + 0x9f10));
        SendDlgItemMessage(dialog, 0x191, 0x0401, 0, 0x7fff, 0);
        SetFocus(GetDlgItem(dialog, 0x191));
        return 0;
    }
    case 0x111:
        break;
    default:
        return 0;
    }

    switch (item) {
    case 1:
        goto selected_name;
    case 2:
        EndDialog(dialog, 0);
        return 0;
    case 0x194:
        break;
    default:
        return 0;
    }

    switch (mode) {
    case 1: {
        if (DlgDirSelect(dialog, path, 0x194)) {
            strcat((char far *)(Dx8 + 0x9f10), path);
        }
        SetDlgItemText(dialog, 0x191, path);
        SendDlgItemMessage(dialog, 0x191, 0x0401, 0, 0x7fff, 0);
        return 1;
    }
    case 2:
        break;
    default:
        return 0;
    }

selected_name:
    if (mode == 2) {
        GetDlgItemText(dialog, 0x191, (char far *)(Dx8 + 0x93a0), 0x80);
        ((char far *)(Dx8 + 0x941f))[0] = 0;
        if (strchr((char far *)(Dx8 + 0x93a0), '*') == 0 &&
            strchr((char far *)(Dx8 + 0x93a0), '?') == 0) {
            if (((char far *)(Dx8 + 0x93a0))[0] == 0)
                MessageBox(dialog, (char far *)(Dx8 + 0x16cf), 0, 0x10);
            else
                EndDialog(dialog, 1);
            return 1;
        }
        last = (char far *)(Dx8 + 0x93a0) +
               strlen((char far *)(Dx8 + 0x93a0));
        if (*last != ':' && *last != '\\' && last > (char far *)(Dx8 + 0x93a0))
            last = AnsiPrev((char far *)(Dx8 + 0x93a0), last);
        prefix[0] = 0;
        if (*last == ':' || *last == '\\') {
            strcpy((char far *)(Dx8 + 0x9f10), last + 1);
            strncpy(prefix, (char far *)(Dx8 + 0x93a0),
                    (unsigned int)(last + 1 - (char far *)(Dx8 + 0x93a0)));
            prefix[(unsigned int)(last + 1 - (char far *)(Dx8 + 0x93a0))] = 0;
        } else {
            strcpy((char far *)(Dx8 + 0x9f10), (char far *)(Dx8 + 0x93a0));
        }
        if (prefix[0])
            strcpy((char far *)(Dx8 + 0x94a0), prefix);
        UpdateListBox(dialog, 0x4010);
        return 1;
    }

    return 0;
}
