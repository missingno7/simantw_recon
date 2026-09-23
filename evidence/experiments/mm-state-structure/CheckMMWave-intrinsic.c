/* C7 baseline profile with a source-local strlen intrinsic hypothesis. */
typedef int (far *MMProc)(void);
extern unsigned int far pascal GetWindowsDirectory(char far *path, unsigned int size);
extern char far * far pascal lstrcat(char far *dest, const char far *source);
extern int far access(const char far *path, int mode);
extern unsigned int far pascal LoadLibrary(const char far *name);
extern MMProc far pascal GetProcAddress(unsigned int module, const char far *name);
extern unsigned int strlen(const char far *text);
#pragma intrinsic(strlen)

struct MultimediaState {
    unsigned int moduleHandle;
    int soundInstalled;
    int waveInstalled;
    int midiHandle;
    void far *midiEntry;
    int waveHandle;
    void far *waveEntry;
    int refCount;
    unsigned int songState;
};
extern __segment near mmSelector;
extern struct MultimediaState __based(mmSelector) soundState;

int CheckMMWave(void)
{
    char path[256];
    MMProc proc;
    int devices;

    GetWindowsDirectory(path, 256);
    if (path[strlen(path) - 1] == '\\')
        lstrcat(path, "system\\mmsystem.dll");
    else
        lstrcat(path, "\\system\\mmsystem.dll");
    if (access(path, 0) == 0) {
        soundState.moduleHandle = LoadLibrary("MMSYSTEM.DLL");
        if (soundState.moduleHandle >= 0x20) {
            proc = GetProcAddress(soundState.moduleHandle, "waveOutGetNumDevs");
            devices = proc ? proc() : 0;
            if (devices != 0)
                return soundState.moduleHandle;
        }
    }
    return 0;
}
