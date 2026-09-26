/* Round 12a: append the default extension when the fallback name lacks a dot. */
/* Round 9: next source family selected from strict aligned residue. */
/* Round 8: residue-specific variant family. */
/* Round 7: direct target binding and unit-shape experiment. */
/* Round 6: call-binding and control-flow hypothesis. */
/* Round 5: evidence-driven stack and call-shape variant. */
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
extern int near hInst;
extern void far * far pascal MakeProcInstance(void far *proc, int instance);
extern void far pascal FreeProcInstance(void far *proc);
extern int far pascal DialogBox(int instance, char far *resource, int owner, void far *proc);
extern int far pascal SetFocus(int window);
extern int far ZapEuMapAt(int, unsigned int, unsigned int, long);
extern char far * strcat(char far *dest, char far *source);
extern char far * strcpy(char far *dest, char far *source);
extern void * memset(void *destination, int value, unsigned int count);
extern int near rootWnd;
extern int far IsDLLAvail(char far *name);
extern int far pascal LoadLibrary(char far *name);
extern FILEDIALOG far pascal GetProcAddress(int module, char far *name);
extern int far access(char far *path, int mode);
extern int far pascal MessageBox(int owner, char far *text,
                                 char far *caption, unsigned int type);
extern int far sprintf(char far *buffer, char far *format, ...);
extern char far * getcwd(char far *buffer, unsigned int count);

int far FileSelect(char far *file, int mode)
{
    char temporary[0x100];
    char currentDirectory[0x80];
    char titleBuffer[0x80];
    char pathBuffer[0x100];
    FILENO ofn;
    FILEDIALOG dialog;
    int module;
    int result;

    if (!IsDLLAvail("COMMDLG.DLL"))
        goto fallback;

    module = LoadLibrary("COMMDLG.DLL");
    if (module < 0x20)
        goto fallback;

    *file = 0;
    {
    FILENO ofn = {0};
    ofn.lStructSize = 0x48L;
    ofn.hwndOwner = rootWnd;
    ofn.hInstance = 0;
    ofn.filter = "SimAnt Files(*.ANT)\0*.ant";
    ofn.customFilter = 0;
    ofn.maxCustomFilter = 0;
    ofn.filterIndex = 1;
    ofn.file = file;
    ofn.maxFile = 0x100L;
    ofn.fileTitle = titleBuffer;
    ofn.maxFileTitle = 0x80L;
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
    if (dialog != 0) {
        result = dialog(&ofn);
        if (result)
            goto accepted;
    }
fallback:
    {
        void far *proc;
        proc = MakeProcInstance((void far *)ZapEuMapAt, hInst);
        result = DialogBox(hInst, mode == 0 ? "Open" : "Save", rootWnd, proc);
        FreeProcInstance(proc);
        SetFocus(rootWnd);
        if (!result)
            return 0;
        getcwd(currentDirectory, 0x100);
        strcpy(pathBuffer, currentDirectory);
        strcat(pathBuffer, file);
        if (strchr(file, '.') == 0) strcat(pathBuffer, ".ant");
        strcpy(file, pathBuffer);
    }
accepted:

    if (mode == 1 && access(file, 0) == 0) {
        char message[256];

        sprintf(message, "Replace existing: %s", file);
        return MessageBox(rootWnd, message, "SimAnt Message", 0x23) == 6;
    }
    return 1;
    }
}
