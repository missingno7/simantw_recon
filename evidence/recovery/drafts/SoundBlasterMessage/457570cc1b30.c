/*
 * Dispatch the callback messages emitted by the multimedia devices.  Message
 * 1 forwards its DWORD payload to sbcCallBack.  Messages 0x14 and 0x28 require
 * their observed payload values, call the corresponding wave procedure, then
 * release and clear the matching three-word channel record.  The multimedia
 * prefix and selector view follow the admitted gr:7712 unit source; the two
 * channel records are an observed adjacent view beginning at songState.
 */
typedef int (far *MMProc)(void);
typedef void (far pascal *MMProc0)(void);
typedef void (far pascal *MMProc1)(unsigned long value);

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

struct SoundChannel {
    int bufferHandle;
    int state;
    int waveHandle;
};

static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
#define stateViaSelector (*(struct MultimediaState __based(mmSelector) *)&mmState)
#define channel0 (*(struct SoundChannel __based(mmSelector) *)&stateViaSelector.songState)
#define channel1 (*(struct SoundChannel __based(mmSelector) *)((char __based(mmSelector) *)&stateViaSelector.songState + 6))

extern MMProc far pascal GetProcAddress(int handle, char far *name);
extern unsigned int far pascal GlobalPageUnlock(unsigned int handle);
extern unsigned int far pascal GlobalUnwire(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);

void far SoundBlasterMessage(unsigned int wMsg, unsigned long dwParam)
{
    MMProc proc;

    if (wMsg == 0x28)
        goto message28;
    if (wMsg > 0x28)
        return;
    switch (wMsg) {
    case 1:
        proc = GetProcAddress(stateViaSelector.moduleHandle, "sbcCallBack");
        if (proc)
            ((MMProc1)proc)(dwParam);
        return;
    case 0x14:
        if ((unsigned int)(dwParam >> 16) != 5)
            return;
        if ((unsigned int)dwParam != 0)
            return;
        proc = GetProcAddress(stateViaSelector.moduleHandle, "waveOutUnprepareHeader");
        if (proc)
            ((MMProc0)proc)();
        GlobalPageUnlock(channel1.waveHandle);
        GlobalUnwire(channel1.bufferHandle);
        GlobalFree(channel1.bufferHandle);
        channel1.bufferHandle = 0;
        channel1.waveHandle = 0;
        channel1.state = 0;
        return;
    }

message28:
    if ((unsigned int)(dwParam >> 16) != 1)
        return;
    if ((unsigned int)dwParam != 0)
        return;
    proc = GetProcAddress(stateViaSelector.moduleHandle, "waveOutReset");
    if (proc)
        ((MMProc0)proc)();
    GlobalPageUnlock(channel0.waveHandle);
    GlobalUnwire(channel0.bufferHandle);
    GlobalFree(channel0.bufferHandle);
    channel0.bufferHandle = 0;
    channel0.waveHandle = 0;
    channel0.state = 0;
}
