/* Round 3, variant 1: far_strcpy_strcat. */
/* Round 1, variant 2: strlib hypothesis. */
/* Test whether the target's two inline copy sequences arise from simple
 * far-string copy loops under C7 optimization rather than library calls. */
extern char far Dx8[];
extern char far *far strcpy(char far *destination, char far *source);
extern char far *far strcat(char far *destination, char far *source);

extern void far *_fmemcpy(void far *destination, const void far *source, unsigned int count);
extern char far *strchr(char far *text, int ch);
extern char far *strstr(char far *text, char near *needle);
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
    char near parentMarker[3] = { '.', '.', 0 };
    char far *source;
    int count;
    int last;
    int i;
    int end;
    unsigned int length;
    SendDlgItemMessage(dialog, 0x194, 0x000b, 0, 0L);
    source = Dx8 + 0x94a0;
    strcpy(buffer, source);
    if (fileType != 0xc010) {
        source = Dx8 + 0x9f10; strcat(buffer, source);
    }
    DlgDirList(dialog, buffer, 0x194, 0x193, fileType);
    source = Dx8 + 0x94a0;
    if (strchr(source, ':') == 0)
        DlgDirList(dialog, Dx8 + 0x9f10, 0x194, 0x193, fileType);
    SendDlgItemMessage(dialog, 0x194, 0x040a, 0, (unsigned long)buffer);
    count = (int)SendDlgItemMessage(dialog, 0x194, 0x040c, 0, 0L);
    if (count <= 0 || buffer[0] == '[') return;
    SendDlgItemMessage(dialog, 0x194, 0x000b, 0, 0L);
    for (;;) {
        last = count - 1;
        SendDlgItemMessage(dialog, 0x194, 0x040a, last, (unsigned long)buffer);
        if (buffer[0] != '[') break;
        SendDlgItemMessage(dialog, 0x194, 0x0403, last, 0L);
        SendDlgItemMessage(dialog, 0x194, 0x0402, 0, (unsigned long)buffer);
        if (buffer[0] != '[') break;
    }
    SendDlgItemMessage(dialog, 0x194, 0x000b, 1, 0L);
    InvalidateRect(GetDlgItem(dialog, 0x194), 0, 1);
    if (strstr(buffer, parentMarker) != 0) *source = 0;
    SetDlgItemText(dialog, 0x191, Dx8 + 0x9f10);
}
