/* _LoadGame: prompt about unsaved work, select and open a saved file,
   initialize the editor/world, and read each segment-8 save record. */
struct LoadRecord { unsigned count; unsigned size; unsigned bufferOffset; unsigned bufferSelector; };
extern char far Dx8[];
extern int far MessageBox(int window, char far *text, char far *caption, unsigned type);
extern int far SaveGame(int allowSave);
extern int far FileSelect(char far *path, int saveMode);
extern char far * far strrchr(const char far *text, int ch);
extern int far stricmp(const char far *left, const char far *right);
extern int far _lopen(char far *path, int mode);
extern int far _lread(int handle, void far *buffer, unsigned count);
extern int far _lclose(int handle);
extern void far Error(char far *message, char far *detail);
extern void far GenerateTutorial(void);
extern void far SetEditWinTitle(char far *title);
extern void far InitSimVars(void);
extern void far SeedSRand(void);
extern void far EditMessage(int a, int b, int c, int d, int e);
extern void far SetDefaultWindows(void);
extern void far CenterEdit(int x, int y);
extern void far RandYard(void);
extern void far DoLoadInitializations(void);
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
extern int far theGameNeedsSaving;
extern int far TutorialMode;

int far LoadGame(void)
{
    char fileName[108];
    char far *baseName;
    struct LoadRecord far *table;
    unsigned long expectedBytes;
    unsigned long totalBytes;
    unsigned record;
    int handle;
    int bytesRead;
    int saveAccepted;
    int result;

    result = 0;
    if (theGameNeedsSaving) {
        saveAccepted = MessageBox(rootWnd, "Save changes first?", "Load Game", 0x1123);
        if (saveAccepted == 2) {
            if (!SaveGame(0))
                goto done;
        } else if (saveAccepted != 1) {
            goto done;
        }
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
        Error("Unable to open save file", sys_errlist[errno]);
        goto done;
    }

    if (stricmp(baseName, "tutorial.ant") == 0) {
        GenerateTutorial();
        SetEditWinTitle("Tutorial");
        InitSimVars();
        SeedSRand();
        EditMessage(0, 0, -2, -1, 1);
        TutorialMode = 1;
    } else {
        SetEditWinTitle(baseName);
    }

    if (theGameNeedsSaving) {
        SetDefaultWindows();
        if (MapPlane != MePlane)
            CenterEdit(MeLocX, MeLocY);
    }

    table = (struct LoadRecord far *)(Dx8 + 0x9570);
    totalBytes = 0;
    for (record = 0; table[record].size != 0; ++record)
        totalBytes += (unsigned long)table[record].count * table[record].size;

    /* Recreate the same map and clear scratch state before loading records. */
    RandYard();
    record = 0;
    while (table[record].size != 0) {
        expectedBytes = (unsigned long)table[record].count * table[record].size;
        bytesRead = _lread(handle,
            (void far *)(((unsigned long)table[record].bufferSelector << 16) |
                         table[record].bufferOffset),
            (unsigned)expectedBytes);
        if (bytesRead != (unsigned)expectedBytes) {
            Error("Invalid save file", "Record length mismatch");
            _lclose(handle);
            goto done;
        }
        ++record;
    }

    Error("", "");
    _lclose(handle);
    DoLoadInitializations();
    SetMenuEntries();
    PauseGame(1);
    if (!TutorialMode)
        StopSong();
    result = 1;

done:
    return result;
}
