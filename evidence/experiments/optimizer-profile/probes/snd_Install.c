/*
 * First-pass reconstruction of multimedia startup.  The selector at
 * DGROUP:0xBF78 reaches SIMANT_DATA_GROUP.  The target reads a word at
 * segment offset 0x8D06, stores module/driver results at 0x8D00..0x8D1C,
 * and uses the same based multimedia state shape as admitted sound helpers.
 * The DLL and procedure names below are the strings at the target's DS
 * offsets 0x0B47..0x0BF1.  This is a bounded semantic candidate, not a
 * claim that the private state object's complete historical extent is known.
 */
typedef int (far pascal *MMProc)(void);
typedef int (far pascal *MMVersionProc)(void);
typedef void far * (far pascal *MMCardProc)(void);

struct MultimediaState {
    int moduleHandle;
    int soundInstalled;
    int waveInstalled;
    int midiHandle;
    void far *midiEntry;
    int waveHandle;
    void far *waveEntry;
    int refCount;
    unsigned int songState;
};

struct SoundInstallRegion {
    int sbcVersion;
    void far *sbcCardName;
    int initialized;
    struct MultimediaState mm;
};

static struct SoundInstallRegion
    __based(__segname("SIMANT_DATA_GROUP")) soundInstall = { 0 };
static const __segment near stateSelector = __segname("SIMANT_DATA_GROUP");
#define state (*(struct SoundInstallRegion __based(stateSelector) *)&soundInstall)
static int __based(__segname("SIMANT_DATA_GROUP")) dsoundModule = 0;

static char near midiOutGetNumDevsName[] = "midiOutGetNumDevs";
static char near waveOutGetNumDevsName[] = "waveOutGetNumDevs";
static char near mmSystemPathInDirectory[] = "system\\mmsystem.dll";
static char near mmSystemPathAtRoot[] = "\\system\\mmsystem.dll";

extern int IsDLLAvail(const char far *name);
extern unsigned int far pascal LoadLibrary(const char far *name);
extern MMProc far pascal GetProcAddress(int handle, char far *name);
extern unsigned int far pascal GetWindowsDirectory(char far *path,
                                                    unsigned int size);
extern char far * far pascal lstrcat(char far *dest, const char far *source);
extern int far access(const char far *path, int mode);
extern int far pascal RegisterWindowMessage(const char far *name);
extern void far WinPrintf(char far *text);
extern int near wSoundBlasterMsg;
extern unsigned int strlen(const char far *text);

void far snd_Install(void)
{
    char path[256];
    MMProc proc;
    MMVersionProc versionProc;
    MMCardProc cardProc;
    int handle;
    struct MultimediaState far *mm;
    int devices;
    unsigned int dsoundVersion;

    if (state.initialized != 0)
        return;

    if (IsDLLAvail("MMSYSTEM.DLL")) {
        mm = (struct MultimediaState far *)&state.mm;
        mm->moduleHandle = LoadLibrary("MMSYSTEM.DLL");
        if (mm->moduleHandle >= 0x20) {
            proc = GetProcAddress(mm->moduleHandle,
                                  midiOutGetNumDevsName);
            devices = proc ? proc() : 0;
            if (devices != 0) {
                mm->soundInstalled = 1;
                goto check_direct_sound;
            }
        }
    }

    if (IsDLLAvail("SNDBLST.DLL")) {
        mm = (struct MultimediaState far *)&state.mm;
        mm->moduleHandle = LoadLibrary("SNDBLST.DLL");
        if (mm->moduleHandle >= 0x20) {
            versionProc = (MMVersionProc)GetProcAddress(
                mm->moduleHandle, "sbcGetDLLVersion");
            cardProc = (MMCardProc)GetProcAddress(
                mm->moduleHandle, "sbcGetCardName");
            if (versionProc != 0 && cardProc != 0) {
                state.sbcVersion = versionProc();
                state.sbcCardName = cardProc();
                if (state.sbcCardName != 0) {
                    wSoundBlasterMsg = RegisterWindowMessage("SoundBlaster");
                    mm->soundInstalled = 0;
                    goto check_direct_sound;
                }
            }
        }
        goto probe_wave_path;
    }

    mm = (struct MultimediaState far *)&state.mm;
    GetWindowsDirectory(path, 256);
    if (path[strlen(path) - 1] == '\\')
        lstrcat(path, mmSystemPathInDirectory);
    else
        lstrcat(path, mmSystemPathAtRoot);
    if (access(path, 0) == 0) {
        mm->moduleHandle = LoadLibrary("MMSYSTEM.DLL");
        if (mm->moduleHandle >= 0x20) {
            proc = GetProcAddress(mm->moduleHandle,
                                  waveOutGetNumDevsName);
            devices = proc ? proc() : 0;
            if (devices != 0)
                mm->waveInstalled = 1;
        }
    }
    if (mm->waveInstalled == 0)
        mm->moduleHandle = 0;
    mm->soundInstalled = 1;
    goto check_direct_sound;

probe_wave_path:
    mm = (struct MultimediaState far *)&state.mm;
    GetWindowsDirectory(path, 256);
    if (path[strlen(path) - 1] == '\\')
        lstrcat(path, mmSystemPathInDirectory);
    else
        lstrcat(path, mmSystemPathAtRoot);
    if (access(path, 0) == 0) {
        mm->moduleHandle = LoadLibrary("MMSYSTEM.DLL");
        if (mm->moduleHandle >= 0x20) {
            proc = GetProcAddress(mm->moduleHandle,
                                  waveOutGetNumDevsName);
            devices = proc ? proc() : 0;
            if (devices == 0)
                mm->waveInstalled = 1;
            else
                mm->moduleHandle = 0;
        } else {
            mm->moduleHandle = 0;
        }
    } else {
        mm->moduleHandle = 0;
    }
    if (mm->moduleHandle == 0)
        mm->soundInstalled = 1;
    else
        mm->waveInstalled = 1;

check_direct_sound:
    if (mm->soundInstalled != 0 && mm->moduleHandle == 0) {
        if (IsDLLAvail("DSOUND.DLL")) {
            dsoundModule = LoadLibrary("DSOUND.DLL");
            if (dsoundModule >= 0x20) {
                proc = GetProcAddress(dsoundModule, "GetDSoundVersion");
                dsoundVersion = proc ? (unsigned int)proc() : 0;
                if (dsoundVersion < 2)
                    WinPrintf("DSound: failure\n");
                else
                    WinPrintf("DSound: success\n");
            } else {
                dsoundModule = 0;
            }
        } else {
            dsoundModule = 0;
        }
    }

    state.initialized = 1;
}
