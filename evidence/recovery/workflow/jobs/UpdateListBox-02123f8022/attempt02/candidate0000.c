/* Recover the observed file-dialog list refresh and selection handling. The
 * constants and control IDs below come from this member's immediate operands. */
extern char far Dx8[];
extern char far *strchr(char far *text, int ch);
extern char far *strstr(char far *text, char near *needle);
extern char far *strcpy(char far *dst, const char far *src);
extern char far *strcat(char far *dst, const char far *src);
extern int far pascal DlgDirList(int dialog, char far *pathSpec, int listId,
                                 int staticId, unsigned int fileType);
extern long far pascal SendDlgItemMessage(int dialog, int item, unsigned int message,
                                         unsigned int wParam, unsigned long lParam);
extern int far pascal GetDlgItem(int dialog, int item);
extern int far pascal InvalidateRect(int window, void far *rect, int erase);
extern int far pascal SetDlgItemText(int dialog, int item, char far *text);

void far UpdateListBox(int dialog, unsigned int fileType)
{
    char buffer[256];
    char far *match;`r`n    char near parentMarker[3] = { \x27.\x27, \x27.\x27, 0 };
    int count;
    int last;

    SendDlgItemMessage(dialog, 0x194, 0x000b, 0, 0L);
    strcpy(buffer, Dx8 + 0x94a0);
    if (fileType != 0xc010)
        strcat(buffer, Dx8 + 0x9f10);
    DlgDirList(dialog, buffer, 0x194, 0x193, fileType);
    match = strchr(buffer, ':');
    if (match == 0)
        DlgDirList(dialog, Dx8 + 0x9f10, 0x194, 0x193, fileType);

    count = (int)SendDlgItemMessage(dialog, 0x194, 0x040a, 0, (unsigned long)buffer);
    if (count <= 0 || buffer[0] == '[')
        return;
    last = count - 1;
    SendDlgItemMessage(dialog, 0x194, 0x040a, last, (unsigned long)buffer);
    if (buffer[0] == '[') {
        SendDlgItemMessage(dialog, 0x194, 0x0403, last, 0L);
        SendDlgItemMessage(dialog, 0x194, 0x0402, 0, (unsigned long)buffer);
        if (buffer[0] == '[')
            return;
    }
    SendDlgItemMessage(dialog, 0x194, 0x000b, 1, 0L);
    InvalidateRect(GetDlgItem(dialog, 0x194), 0, 1);
    if (strstr(buffer, parentMarker) == 0)
        buffer[0] = 0;
    SetDlgItemText(dialog, 0x191, Dx8 + 0x9f10);
}

