/* Round 4: distinct branch and local-layout hypothesis. */
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
extern void * memset(void *destination, int value, unsigned int count);
extern void far * far pascal MakeProcInstance(void far *proc, int instance);
extern void far pascal FreeProcInstance(void far *proc);
extern int far pascal DialogBox(int instance, char far *resource, int owner,
                                void far *proc);
extern int far ZapEuMapAt(int, unsigned int, unsigned int, long);

int far FileSelect(char far *file, int mode)
{
    FILENO ofn;
    FILEDIALOG dialog;
    int module;
    int result;

    if (!IsDLLAvail("COMMDLG.DLL"))
        goto legacy_dialog;

    module = LoadLibrary("COMMDLG.DLL");
    if (module < 0x20)
        goto legacy_dialog;

    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = 0x48L;
    ofn.hwndOwner = rootWnd;
    ofn.hInstance = 0;
    ofn.filter = "SimAnt Files(*.ANT)\0*.ant";
    ofn.filterIndex = 1;
    ofn.file = file;
    ofn.maxFile = 0x100L;
    ofn.title = mode == 0 ? "Load Ant Hill" : "Save Ant Hill As";

    ofn.defaultExtension = "ant";

    if (mode == 0) {
        dialog = GetProcAddress(module, "GetOpenFileName");
        ofn.flags = 0x1800L;
    } else {
        dialog = GetProcAddress(module, "GetSaveFileName");
        ofn.flags = 0x0802L;
    }
    if (dialog == 0)
        goto legacy_dialog;

    result = dialog(&ofn);
    if (!result)
        return 0;
    goto accepted;

legacy_dialog:
    {
        void far *proc;
        proc = MakeProcInstance((void far *)ZapEuMapAt, 0);
        result = DialogBox(0, "ZapEuMapAt", rootWnd, proc);
        FreeProcInstance(proc);
        if (!result)
            return 0;
    }
accepted:
    *file = 0;

    if (mode == 1 && access(file, 0) == 0) {
        char message[256];

        sprintf(message, "Replace existing: %s", file);
        return MessageBox(rootWnd, message, "SimAnt Message", 0x23) == 6;
    }
    return 1;
}
