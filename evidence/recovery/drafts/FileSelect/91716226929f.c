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
extern char far * far strcat(char far *dest, char far *source);
extern char far * far strncpy(char far *dest, char far *source, unsigned int count);
extern unsigned char near _ctype[];
extern char far * far strcpy(char far *dest, char far *source);
extern void *memset(void *destination, int value, unsigned int count);
extern unsigned int far strlen(char far *text);
extern int near rootWnd;
extern int far IsDLLAvail(char far *name);
extern int far pascal LoadLibrary(char far *name);
extern FILEDIALOG far pascal GetProcAddress(int module, char far *name);
extern int far access(char far *path, int mode);
extern int far pascal MessageBox(int owner, char far *text,
                                 char far *caption, unsigned int type);
extern void far * far _fmemcpy(void far *destination, const void far *source, unsigned int count);
extern int far sprintf(char far *buffer, char far *format, ...);
extern char far * getcwd(char far *buffer, unsigned int count);

int far FileSelect(char far *file, int mode)
{
    char temporary[30];
    char currentDirectory[0x100];
    char titleBuffer[0x20];
    char extension[0x10];
    FILENO ofn;
    FILEDIALOG dialog;
    unsigned int module;
    int result;
    unsigned int sourceLength;

    if (!IsDLLAvail("COMMDLG.DLL"))
        goto fallback;

    module = LoadLibrary("COMMDLG.DLL");
    if (module < 0x20)
        goto fallback;

    *file = 0;
    {
    FILENO ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = 0x48L;
    ofn.hwndOwner = rootWnd;
    ofn.filter = "SimAnt Files(*.ANT)\0*.ant";
    ofn.filterIndex = 1;
    ofn.file = file;
    ofn.maxFile = 0x100L;
    ofn.defaultExtension = "ant";

    if (mode == 0) {
        dialog = GetProcAddress(module, "GetOpenFileName");
        ofn.flags = 0x1800L;
        ofn.title = "Load Ant Hill";
        if (dialog != 0) {
            result = dialog(&ofn);
            if (result)
                goto accepted;
        }
    } else {
        dialog = GetProcAddress(module, "GetSaveFileName");
        ofn.flags = 0x0802L;
        ofn.title = "Save Ant Hill As";
        if (dialog != 0) {
            result = dialog(&ofn);
            if (result)
                goto accepted;
        }
    }
fallback:
    {
        void far *proc;
        char far *selected;
        char far *dot;

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
        sourceLength = strlen(selected);
        for (sourceLength = 0; selected[sourceLength] != 0; ++sourceLength) {
            char c;
            c = selected[sourceLength];
            if (!(_ctype[(int)c + 1] & 7) && c != '.' && c != ':' && c != '\\')
                selected[sourceLength] = '_';
        }
        sourceLength = strlen(selected);
        if (sourceLength > 0x0c) {
            strncpy(titleBuffer, selected, 8);
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
            if (currentDirectory[0] && currentDirectory[strlen(currentDirectory) - 1] == '\\')
                sprintf(ofn.file, "%s%s%s", currentDirectory, titleBuffer, extension);
            else
                sprintf(ofn.file, "%s\\%s%s", currentDirectory, titleBuffer, extension);
        } else {
            if (currentDirectory[0] && currentDirectory[strlen(currentDirectory) - 1] == '\\')
                sprintf(ofn.file, "%s%s", currentDirectory, selected);
            else
                sprintf(ofn.file, "%s\\%s", currentDirectory, selected);
        }
    }
accepted:

    if (mode == 1 && access(ofn.file, 0) == 0) {
        char message[256];

        sprintf(message, "Replace existing: %s", ofn.file);
        return MessageBox(rootWnd, message, "SimAnt Message", 0x23) == 6;
    }
    return 1;
    }

}