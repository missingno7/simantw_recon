/* The SAVEASDLG callback edits the file pattern and the current directory. */
struct VersionTableView {
    unsigned char bufferData[480];
    unsigned int header[2];
    unsigned char entries[2456];
    unsigned long reservedTail;
    char filePattern[4];
    unsigned char trailingZeroes[12];
};
extern struct VersionTableView
    __based(__segname("SIMANT_DATA_GROUP")) versionStr;
extern char __based(__segname("DGROUP")) curFontPtr[];

extern void near UpdateListBox(int dialog, unsigned int fileType);
extern int far pascal SetDlgItemText(int dialog, unsigned item,
                                     char far *text);
extern int far pascal GetDlgItemText(int dialog, int item, char far *text, int count);
extern long far pascal SendDlgItemMessage(int dialog, unsigned item,
                                           unsigned message, unsigned wParam,
                                           unsigned long lParam);
extern int far pascal GetDlgItem(int dialog, unsigned item);
extern int far pascal SetFocus(int window);
extern int far pascal EndDialog(int dialog, int result);
extern int far pascal DlgDirSelect(int dialog, char far *buffer, int item);
extern unsigned int far pascal lstrlen(char far *text);
extern char far * far pascal lstrcpy(char far *destination,
                                     char far *source);
extern char far * far strcpy(char far *destination, char far *source);
extern char far * far strcat(char far *destination, char far *source);
extern char far * far strchr(char far *text, int ch);
extern unsigned int strlen(char far *text);
extern void far *_fmemcpy(void far *destination, const void far *source,
                          unsigned int count);
extern char far * far pascal AnsiPrev(char far *start, char far *current);
extern int far pascal MessageBox(int dialog, char far *text,
                                char far *caption, unsigned type);

int far pascal SAVEASDLG(int dialog, unsigned message, int command,
                         int notification, int arg0)
{
    char pathText[256];
    char fileText[256];
    char far *input;
    char far *rootPath;
    long result;

    (void)arg0;
    switch (message) {
    case 0x110:
    {
        UpdateListBox(dialog, 0xc010);
        SetDlgItemText(dialog, 0x191, versionStr.filePattern);
        SendDlgItemMessage(dialog, 0x191, 0x401, 0, 0x10000L);
        SetFocus(GetDlgItem(dialog, 0x191));
        return 1;
    }
    case 0x111:
        switch (command) {
        case 1:
        {
            char far *end;
            char far *last;
            unsigned int length;

            input = &versionStr.bufferData[0x10];
            rootPath = &versionStr.bufferData[0x110];
            GetDlgItemText(dialog, 0x194, input, 0x80);
            versionStr.bufferData[0x8f] = 0;

            if (strchr(input, '*') == 0 && strchr(input, '?') == 0) {
                result = SendDlgItemMessage(dialog, 0x194, 0x409, 0, 0L);
                if (result == -1L) {
                    if (input[0] == 0)
                        MessageBox(dialog, curFontPtr + 0x60, 0, 0x10);
                    else
                        SetFocus(GetDlgItem(dialog, 1));
                    return 1;
                }
            }

            length = lstrlen(input);
            end = input + length;
            last = end;
            if (last > input)
                last = AnsiPrev(input, last);
            if (last > input && (*last == ':' || *last == '\\')) {
                lstrcpy(versionStr.filePattern, last + 1);
                lstrcpy(pathText, input);
                pathText[(unsigned int)(last - input) + 1] = 0;
            } else {
                lstrcpy(versionStr.filePattern, input);
                pathText[0] = 0;
            }

            if (pathText[0] != 0)
                _fmemcpy(rootPath, pathText, strlen(pathText) + 1);
            UpdateListBox(dialog, 0xc010);
            return 1;
        }

        case 2:
            EndDialog(dialog, 0);
            return 0;

        case 0x194:
            switch (notification) {
            case 1:
            {
            if (DlgDirSelect(dialog, fileText, 0x194))
                strcat(fileText, versionStr.filePattern);
            SetDlgItemText(dialog, 0x191, fileText);
            SendDlgItemMessage(dialog, 0x191, 0x401, 0, 0x7fff0000L);
            return 1;
            }

            case 2:
            {
                char far *notifyEnd;
                char far *notifyLast;
                unsigned int notifyLength;
                input = &versionStr.bufferData[0x10];
                rootPath = &versionStr.bufferData[0x110];
                GetDlgItemText(dialog, 0x191, input, 0x80);
                versionStr.bufferData[0x8f] = 0;

                if (strchr(input, '*') == 0 && strchr(input, '?') == 0) {
                    result = SendDlgItemMessage(dialog, 0x194, 0x409, 0, 0L);
                    if (result == -1L) {
                        if (input[0] == 0)
                            MessageBox(dialog, curFontPtr + 0x60, 0, 0x10);
                        else
                            SetFocus(GetDlgItem(dialog, 1));
                        return 1;
                    }
                }

                notifyLength = lstrlen(input);
                notifyEnd = input + notifyLength;
                notifyLast = notifyEnd;
                if (notifyLast > input)
                    notifyLast = AnsiPrev(input, notifyLast);
                if (notifyLast > input &&
                    (*notifyLast == ':' || *notifyLast == '\\')) {
                    lstrcpy(versionStr.filePattern, notifyLast + 1);
                    lstrcpy(pathText, input);
                    pathText[(unsigned int)(notifyLast - input) + 1] = 0;
                } else {
                    lstrcpy(versionStr.filePattern, input);
                    pathText[0] = 0;
                }

                if (pathText[0] != 0)
                    _fmemcpy(rootPath, pathText, strlen(pathText) + 1);
                UpdateListBox(dialog, 0xc010);
                return 1;
            }
            default:
                return 1;
            }
        default:
            return 0;
        }
    default:
        return 0;
    }
}
