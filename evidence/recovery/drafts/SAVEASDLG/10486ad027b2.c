/* SAVEASDLG: handle the dialog's initialization and command notifications.
   The selected name is normalized, copied to the dialog controls, and then
   passed to the list-refresh or close path. */
extern void near UpdateListBox(int dialog);
extern int far pascal SetDlgItemText(int dialog, unsigned item, char far *text);
extern int far pascal GetDlgItemText(int dialog, unsigned item, char far *text, int maxChars);
extern long far pascal SendDlgItemMessage(int dialog, unsigned item, unsigned message,
                                          unsigned wParam, unsigned long lParam);
extern int far pascal GetDlgItem(int dialog, unsigned item);
extern int far pascal SetFocus(int window);
extern int far pascal EndDialog(int dialog, int result);
extern int far pascal DlgDirSelect(int dialog, char far *buffer, int maxChars, int item);
extern int far Lstrlen(char far *text);
extern char far * far Lstrcpy(char far *dest, char far *src);
extern char far * far AnsiPrev(char far *start, char far *current);
extern char far * far strchr(char far *text, int ch);
extern int far MessageBox(int dialog, char far *text, char far *caption, unsigned type);
extern int far Dx8[];

int far pascal SAVEASDLG(int arg0, int arg1, int command, unsigned message, int dialog)
{
    char path[128];
    char scratch[260];
    char far *p;
    char far *q;
    int length;
    int commandResult;

    commandResult = 0;
    if (message == 0x110) {
        UpdateListBox(dialog);
        SetDlgItemText(dialog, 0x191, "Files");
        SendDlgItemMessage(dialog, 0x191, 0x401, 1, 0L);
        SetFocus(GetDlgItem(dialog, 0x191));
        return 1;
    }
    if (message != 0x111)
        return 0;

    if (command == 2) {
        EndDialog(dialog, 0);
        return 1;
    }
    if (command == 1) {
        length = GetDlgItemText(dialog, 0x194, path, sizeof(path));
        if (length == 0) {
            DlgDirSelect(dialog, path, sizeof(path), 0x194);
            UpdateListBox(dialog);
            return 1;
        }
        p = strchr(path, ':');
        q = strchr(path, '\\');
        if (p == 0 && q == 0) {
            Lstrcpy(scratch, path);
            Lstrcpy(path, "*.*");
            Lstrlen(scratch);
        }
        if (path[0] == 0) {
            MessageBox(dialog, "Enter a file name", "Save As", 0x10);
            SetFocus(GetDlgItem(dialog, 0x194));
            return 1;
        }
        SetDlgItemText(dialog, 0x191, path);
        UpdateListBox(dialog);
        EndDialog(dialog, 1);
        return 1;
    }
    if (command == 0x192 || command == 0x194) {
        GetDlgItemText(dialog, 0x194, path, sizeof(path));
        DlgDirSelect(dialog, path, sizeof(path), 0x191);
        p = strchr(path, ':');
        q = strchr(path, '\\');
        if (p == 0 && q != 0)
            AnsiPrev(path, q);
        SetDlgItemText(dialog, 0x191, path);
        SendDlgItemMessage(dialog, 0x191, 0x401, 0, 0x7fffL);
        UpdateListBox(dialog);
        return 1;
    }
    if (command == 0x401) {
        EndDialog(dialog, 1);
        return 1;
    }
    (void)arg0;
    (void)arg1;
    (void)commandResult;
    (void)Dx8[0];
    return 0;
}
