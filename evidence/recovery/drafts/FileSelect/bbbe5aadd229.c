/* Round 2: independent source-shape hypothesis. */
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
    char currentDirectory[128];
    char workPath[256];
    FILENO ofn;
    FILEDIALOG dialog;
    int module;
    int result;
    int pathLength;

    *file = 0;
    if (!IsDLLAvail("COMMDLG.DLL"))
        return 0;

    module = LoadLibrary("COMMDLG.DLL");
    if (module < 0x20)
        return 0;

    ofn.lStructSize = 0x48L;
    ofn.hwndOwner = rootWnd;
    ofn.hInstance = 0;
    ofn.filter = "SimAnt Files(*.ANT)\0*.ant";
    ofn.customFilter = 0;
    ofn.maxCustomFilter = 0;
    ofn.filterIndex = 1;
    ofn.file = file;
    ofn.maxFile = 0x100L;
    ofn.fileTitle = 0;
    ofn.maxFileTitle = 0;
    if (getcwd(currentDirectory, sizeof(currentDirectory)) != 0)
        ofn.initialDirectory = currentDirectory;
    else
        ofn.initialDirectory = 0;
    ofn.title = mode == 0 ? "Load Ant Hill" : "Save Ant Hill As";
    ofn.flags = mode == 0 ? 0x1800L : 0x0802L;
    ofn.fileOffset = 0;
    ofn.extensionOffset = 0;
    ofn.defaultExtension = "ant";
    ofn.customData = 0;
    ofn.hook = 0;
    ofn.templateName = 0;

    if (mode == 0)
        dialog = GetProcAddress(module, "GetOpenFileName");
    else
        dialog = GetProcAddress(module, "GetSaveFileName");
    if (dialog == 0)
        return 0;

    result = dialog(&ofn);
    if (!result)
        return 0;
    pathLength = 0;
    while (file[pathLength] != 0 && pathLength < 255) {
        workPath[pathLength] = file[pathLength];
        ++pathLength;
    }
    workPath[pathLength] = 0;

    if (mode == 1 && access(file, 0) == 0) {
        char message[256];

        sprintf(message, "Replace existing: %s", file);
        return MessageBox(rootWnd, message, "SimAnt Message", 0x23) == 6;
    }
    return 1;
}
