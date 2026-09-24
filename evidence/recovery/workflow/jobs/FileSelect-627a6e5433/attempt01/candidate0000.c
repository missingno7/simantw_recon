/*
 * FileSelect opens the Windows common file dialog and returns whether the
 * caller accepted a file.  Its input is a far output buffer; its capacity is
 * not inferred from the two callers here.
 */
typedef struct tagFileOpenName {
    unsigned long lStructSize;
    int hwndOwner;
    int hInstance;
    char far *filter;
    char far *customFilter;
    unsigned long maxCustomFilter;
    unsigned long filterIndex;
    char far *file;
    unsigned long maxFile;
    char far *fileTitle;
    unsigned long maxFileTitle;
    char far *initialDirectory;
    char far *title;
    unsigned long flags;
    unsigned int fileOffset;
    unsigned int extensionOffset;
    char far *defaultExtension;
    unsigned long customData;
    void (far pascal *hook)(void);
    char far *templateName;
} FILENO;

typedef int (far pascal *FILEDIALOG)(FILENO far *);

extern char far Dx8[];
extern int near rootWnd;
extern int far pascal IsDLLAvail(char far *name);
extern int far pascal LoadLibrary(char far *name);
extern FILEDIALOG far pascal GetProcAddress(int module, char far *name);
extern int far access(char far *path, int mode);
extern int far pascal MessageBox(int owner, char far *text,
                                 char far *caption, unsigned int type);
extern int far sprintf(char far *buffer, char far *format, ...);

int far FileSelect(char far *file, int mode)
{
    FILENO ofn;
    FILEDIALOG dialog;
    int module;
    int result;

    *file = 0;
    if (!IsDLLAvail(Dx8 + 0x16fd))
        return 0;

    module = LoadLibrary(Dx8 + 0x1709);
    if (module < 0x20)
        return 0;

    ofn.lStructSize = 0x48L;
    ofn.hwndOwner = rootWnd;
    ofn.hInstance = 0;
    ofn.filter = Dx8 + 0x1715;
    ofn.customFilter = 0;
    ofn.maxCustomFilter = 0;
    ofn.filterIndex = 1;
    ofn.file = file;
    ofn.maxFile = 0x100L;
    ofn.fileTitle = 0;
    ofn.maxFileTitle = 0;
    ofn.initialDirectory = 0;
    ofn.title = Dx8 + (mode == 0 ? 0x1745 : 0x1763);
    ofn.flags = mode == 0 ? 0x1800L : 0x0802L;
    ofn.fileOffset = 0;
    ofn.extensionOffset = 0;
    ofn.defaultExtension = Dx8 + 0x1731;
    ofn.customData = 0;
    ofn.hook = 0;
    ofn.templateName = 0;

    if (mode == 0)
        dialog = GetProcAddress(module, Dx8 + 0x1735);
    else
        dialog = GetProcAddress(module, Dx8 + 0x1753);
    if (dialog == 0)
        return 0;

    result = dialog(&ofn);
    if (!result)
        return 0;

    if (mode == 1 && access(file, 0) == 0) {
        char message[256];

        sprintf(message, Dx8 + 0x17b9, file);
        return MessageBox(rootWnd, message, Dx8 + 0x17ce, 0x23) == 6;
    }
    return 1;
}
