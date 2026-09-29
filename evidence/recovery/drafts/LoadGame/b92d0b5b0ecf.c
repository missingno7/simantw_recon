/* _LoadGame: prompt about unsaved work, select and open a saved file,
   initialize the editor/world, and read each segment-8 save record. */
struct LoadRecord { unsigned count; unsigned size; void far *buffer; };
extern unsigned char far Dx8[];
extern int far pascal MessageBox(int window, char far *text, char far *caption, unsigned type);
extern int far SaveGame(int allowSave);
extern int far FileSelect(char far *path, int saveMode);
extern char far * far strrchr(const char far *text, int ch);
extern int far stricmp(const char far *left, const char far *right);
extern int far pascal _lopen(char far *path, int mode);

extern int far pascal _lread(int file, void far *buffer, int bytes);

extern int far pascal _lclose(int handle);

extern void far Error(char far *message);
extern void far GenerateTutorial(void);
extern void far SetEditWinTitle(char far *title);
extern void far InitSimVars(void);
extern void far SeedSRand(void);
extern void far EditMessage(int a, int b, int c, int d, int e);
extern void far SetDefaultWindows(void);
extern void far CenterEdit(int x, int y);
extern void far RandYard(void);
extern int far DoLoadInitializations(void);

extern void far SetMenuEntries(void);
extern void far PauseGame(int paused);
extern void far StopSong(void);
extern int near rootWnd;
extern int near MapPlane;
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near errno;
extern char far * far sys_errlist[];
extern int far gGameNeedsSaving;
extern int far OptionStates[];
extern int far JustXfered;
extern unsigned long far LastThemeTime;
extern unsigned long far TimeTemp;
extern unsigned long far EditMsgDelay;
extern int far CurGameType;

int far LoadGame(void)
{
    char fileName[100];
    char far *baseName;
    struct LoadRecord far *table;
    unsigned expectedBytes;
    register unsigned totalBytes;
    int handle;
    int saveAccepted;
    register int proceed;
    int result;

    result = 0;
    if (gGameNeedsSaving) {
        proceed = 0;
        do {
            saveAccepted = MessageBox(rootWnd, "Save changes first?", "Load Game", 0x1123);
            switch (saveAccepted) {
            case 2:
                goto done;
            case 6:
                if (!SaveGame(0))
                    break;
            default:
                proceed = 1;
                break;
            }
        } while (!proceed);
    }

    if (FileSelect(fileName, 0))
        goto done;

    /* Preserve the selected path as the next dialog's default name. */
    strcpy((char far *)(Dx8 + 0x9520), fileName);
    baseName = strrchr(fileName, '\\');
    if (baseName)
        ++baseName;
    else
        baseName = fileName;

    handle = _lopen(fileName, 0);
    if (handle < 0) {
        Error(sys_errlist[errno]);
        goto done;
    }

    if (stricmp(baseName, "tutorial.ant") == 0) {
        GenerateTutorial();
        SetEditWinTitle("Tutorial");
        InitSimVars();
        SeedSRand();
        EditMessage(0, 0, -2, -1, 1);
        OptionStates[1] = 1;
    } else {
        SetEditWinTitle(baseName);
    }

    if (gGameNeedsSaving) {
        SetDefaultWindows();
        if (MapPlane != MePlane)
            CenterEdit(MeLocX, MeLocY);
    }

    JustXfered = 1;
    LastThemeTime = 0;
    TimeTemp = 300L;
    EditMsgDelay = 0;
    CurGameType = -1;

    table = (struct LoadRecord far *)(Dx8 + 0x9570);
    totalBytes = 0;
    while (table->size != 0) {
        totalBytes += table->count * table->size;
        ++table;
    }

    /* Recreate the same map and clear scratch state before loading records. */
    RandYard();
    table = (struct LoadRecord far *)(Dx8 + 0x9570);
    while (table->size != 0) {
        expectedBytes = table->count * table->size;
        if (_lread(handle, table->buffer, expectedBytes) != expectedBytes) {
            Error("  Read error  \ngame not loaded");
            _lclose(handle);
            goto done;
        }
        ++table;
    }

    Error("", "");
    _lclose(handle);
    DoLoadInitializations();
    SetMenuEntries();
    PauseGame(1);
    if (!OptionStates[1])
        StopSong();
    result = 1;

done:
    return result;
}
