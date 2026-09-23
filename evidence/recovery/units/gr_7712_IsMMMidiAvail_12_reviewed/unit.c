/* Reviewed multimedia unit extension: twelve claimed members in MAPSYM
 * order, with one shared 22-byte far state at SIMANT_DATA_GROUP 8D08.
 * Code runs leave unrecovered functions unclaimed. */

typedef int (far *MMProc)(void);
typedef void (far pascal *MMCloseProc)(int handle);
extern MMProc far pascal GetProcAddress(int handle, char far *name);
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
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};
static int near vocBufLocked1 = 0;
static int near vocBufLocked2 = 0;
/* MAPSYM names these adjacent near words at DGROUP AF4, AF6 and AF8. */
int near wSoundBlasterMsg = 0;
int near songsOnFlag = 0;
int near effectsOnFlag = 0;
extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern void far WinPrintf(char far *text);
extern int far pascal MessageBeep(unsigned int type);
extern unsigned long far FlipLong(unsigned long value);
extern unsigned short FlipWord(unsigned short);
struct ThreeBytes {
    unsigned char b[3];
};
extern void far myBeginSound(unsigned int first,
                             unsigned int second,
                             unsigned int third);


void far vocMciClose(unsigned int buffer1, unsigned int buffer2);
int snd_IsSongDone(void);
void far poolstub_sound_before_voc(void);
void far poolstub_sound_after_voc(void);
void MusicInit(void);
void SysBeep(void);
void myBeginSoundList(void);
void ExtractDWord(void far * far *p, unsigned long far *out);
void ExtractWord(void far * far *p,unsigned short far *out);
void far Extract24BitVal(void far * far *cursor, unsigned long far *value, long far *remaining);
int mySoundIsDone(void);
void myBeginSoundReverse(unsigned int first, unsigned int second, unsigned int third);

#pragma alloc_text(RUN2_TEXT, snd_IsSongDone)
#pragma alloc_text(RUN3_TEXT, vocMciClose)
#pragma alloc_text(RUN4_TEXT, MusicInit, SysBeep, myBeginSoundList)
#pragma alloc_text(RUN5_TEXT, ExtractDWord, ExtractWord)
#pragma alloc_text(RUN6_TEXT, Extract24BitVal)
#pragma alloc_text(RUN7_TEXT, mySoundIsDone, myBeginSoundReverse)
#pragma alloc_text(POOLSTUB_TEXT, poolstub_sound_before_voc, poolstub_sound_after_voc)

int IsMMMidiAvail(void)
{
    MMProc proc;

    proc = GetProcAddress(mmState.moduleHandle, "midiOutGetNumDevs");
    if (proc)
        return proc();
    return 0;
}

int IsMMWaveAvail(void)
{
    MMProc proc;

    proc = GetProcAddress(mmState.moduleHandle, "waveOutGetNumDevs");
    if (proc)
        return proc();
    return 0;
}

int snd_IsSongDone(void)
{
    if (mmState.moduleHandle == 0 ||
        mmState.waveInstalled != 0 ||
        mmState.soundInstalled != 0)
        return 1;
    return mmState.songState < 1;
}

/* Noncredited stand-in: observed literals between the admitted availability
 * routines and vocMciClose. The original owners remain unrecovered. */
void far poolstub_sound_before_voc(void)
{
    char near * volatile p;
    p = "system\\mmsystem.dll";
    p = "\\system\\mmsystem.dll";
    p = "MMSYSTEM.DLL";
    p = "\\";
    p = "\\";
    p = "\\";
    p = "MMSYSTEM.DLL";
    p = "MMSYSTEM.DLL";
    p = "SNDBLST.DLL";
    p = "SNDBLST.DLL";
    p = "sbcGetDLLVersion";
    p = "sbcGetCardName";
    p = "SoundBlaster";
    p = "DSOUND.DLL";
    p = "DSOUND.DLL";
    p = "GetDSoundVersion";
    p = "DSound: success\n";
    p = "DSound: failure\n";
    p = "mciSendCommand";
    p = "Midi: Close Device\n";
    p = "waveOutClose";
    p = "sbcTerminateDLL";
    p = "waveOutClose";
    p = "musCloseDevice";
    p = "vocCloseDevice";
}

void far vocMciClose(unsigned int buffer1, unsigned int buffer2)
{
    MMCloseProc proc;
    if (vocBufLocked2) {
        GlobalUnlock(buffer2);
        GlobalFree(buffer2);
        vocBufLocked2 = 0;
    }
    if (vocBufLocked1) {
        GlobalUnlock(buffer1);
        GlobalFree(buffer1);
        vocBufLocked1 = 0;
    }
    if (--mmState.refCount == 0) {
        proc = (MMCloseProc)GetProcAddress(mmState.moduleHandle, "waveOutClose");
        if (proc)
            proc(mmState.waveHandle);
        mmState.waveHandle = 0;
    }
}

/* Noncredited stand-in for the three strings after vocMciClose. */
void far poolstub_sound_after_voc(void)
{
    char near * volatile p;
    p = "sbcCallBack";
    p = "waveOutReset";
    p = "waveOutUnprepareHeader";
}

void MusicInit(void)
{
    WinPrintf("MUSIC INIT!");
}

void SysBeep(void)
{
    MessageBeep(0);
}

void myBeginSoundList(void)
{
}

void ExtractDWord(void far * far *p, unsigned long far *out)
{
    *out = *(unsigned long far *)*p;
    *out = FlipLong(*out);
    *p = (void far *)((unsigned long)*p + 4);
}

void ExtractWord(void far * far *p,unsigned short far *out) { *out=*(unsigned short far *)*p; *out=FlipWord(*out); *p=(void far *)((unsigned long)*p+2); }

void far Extract24BitVal(void far * far *cursor, unsigned long far *value,
                         long far *remaining)
{
    *value = 0;
    *(struct ThreeBytes far *)((unsigned long)value + 1) =
        *(struct ThreeBytes far *)*cursor;
    *value = FlipLong(*value);
    *cursor = (void far *)((unsigned long)*cursor + 3);
    *remaining -= 3;
}

int mySoundIsDone(void)
{
    return 1;
}

void myBeginSoundReverse(unsigned int first,
                         unsigned int second,
                         unsigned int third)
{
    myBeginSound(first, second, third);
}

