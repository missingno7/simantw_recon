/* Round 32b: format the normalized existing path in the replacement prompt. */
/* Round 31d: test existing-file status against the normalized full path. */
/* Round 22a: gate 8.3 basename staging on the target twelve-character limit. */
/* Round 20a: stage eight base-name bytes, supply ANT when absent, then join cwd. */
/* Round 18a: preserve the separator construction and bound the output copy. */
/* Round 13b: insert a directory separator between cwd and the fallback name. */
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
    char currentDirectory[0x100];
    char titleBuffer[0x20];
    char extension[0x10];
    char pathBuffer[0x100];
    FILENO ofn;
    FILEDIALOG dialog;
    unsigned int module;
    int result;
    int sourceLength;

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
        char far *selected;
        char far *dot;
        int i;

        proc = MakeProcInstance((void far *)ZapEuMapAt, hInst);
        result = DialogBox(hInst, mode == 0 ? "Open" : "Save", rootWnd, proc);
        FreeProcInstance(proc);
        SetFocus(rootWnd);
        if (!result)
            return 0;

        getcwd(currentDirectory, 0x100);
        selected = Dx8;
        selected += 0x93a0;
        strcpy(temporary, selected);
        sourceLength = 0;
        while (selected[sourceLength] != 0) {
            unsigned char c;
            c = selected[sourceLength];
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
                  (c >= '0' && c <= '9')) && c != '.' && c != ':' && c != '\\')
                selected[sourceLength] = '_';
            ++sourceLength;
        }
        sourceLength = 0;
        while (selected[sourceLength] != 0)
            ++sourceLength;
        if (sourceLength > 0x0c) {
            for (i = 0; i < 8; ++i)
                titleBuffer[i] = selected[i];
            titleBuffer[8] = 0;
            dot = strchr(titleBuffer, '.');
            if (dot != 0) {
                extension[0] = '.';
                extension[1] = dot[1];
                extension[2] = dot[2];
                extension[3] = dot[3];
                extension[4] = 0;
            } else {
                extension[0] = '.';
                extension[1] = 'A';
                extension[2] = 'N';
                extension[3] = 'T';
                extension[4] = 0;
            }
            if (currentDirectory[0] && currentDirectory[lstrlen(currentDirectory) - 1] == '\\')
                sprintf(file, "%s%s%s", currentDirectory, titleBuffer, extension);
            else
                sprintf(file, "%s\\%s%s", currentDirectory, titleBuffer, extension);
        } else {
            if (currentDirectory[0] && currentDirectory[lstrlen(currentDirectory) - 1] == '\\')
                sprintf(file, "%s%s", currentDirectory, selected);
            else
                sprintf(file, "%s\\%s", currentDirectory, selected);
        }
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