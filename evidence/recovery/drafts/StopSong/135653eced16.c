/*
 * StopSong: stop the current MIDI/SoundBlaster song through the private
 * multimedia module state (SIMANT_DATA_GROUP, same object family as the
 * admitted IsMMWaveAvail/musSoundBlasterClose/vocMciClose: module handle
 * at 0x8d08, plus unnamed flag/handle words at 0x8d0a/0x8d0c/0x8d0e/
 * 0x8d1c/0x8d1e/0x8d20).  If the module isn't loaded, or the "installed"
 * flag (0x8d0c) is clear, just call the legacy CLOSESOUND driver entry.
 * Otherwise, when the MCI flag (0x8d0a) is set, resolve and invoke
 * mciSendCommand to close the MCI device (logging "Midi: Close Device")
 * and clear the device id; when clear, resolve and invoke musStopMusic
 * (logging any nonzero error via "SBPro Error(musStopMusic)(%u)") and
 * musCloseDevice, then release the wired page/handle and zero the three
 * state words.  GetProcAddress names come from the wSoundBlasterMsg near
 * string table (base 0xaf4, matching the admitted siblings).
 */
typedef void (far pascal *VoidProc)(void);
typedef unsigned int (far pascal *ErrProc)(void);
typedef void (far pascal *MciProc)(unsigned int deviceId, unsigned int msg,
                                    unsigned long flags, void far *params);

extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) mmModule;
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) mmMciFlag;
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) mmInstalledFlag;
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) mmDeviceId;
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) mmHandle;
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) mmStateWord;
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) mmPage;

extern void far * pascal GetProcAddress(unsigned int handle, char far *name);
extern unsigned int far pascal GlobalPageUnlock(unsigned int handle);
extern unsigned int far pascal GlobalUnwire(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern void far pascal CloseSound(void);
extern void far WinPrintf(char far *format, ...);
extern char near wSoundBlasterMsg[];

void far StopSong(void)
{
    long mciParams[4];
    MciProc mciProc;
    ErrProc stopProc;
    VoidProc closeProc;
    unsigned int err;

    if (mmModule == 0 || mmInstalledFlag == 0) {
        CloseSound();
        return;
    }

    if (mmMciFlag != 0) {
        mciProc = (MciProc)GetProcAddress(mmModule, wSoundBlasterMsg + 0x1c2);
        WinPrintf("Midi: Close Device\n");
        if (mciProc != 0)
            mciProc(mmDeviceId, 0x804, 0, mciParams);
        mmDeviceId = 0;
        return;
    }

    stopProc = (ErrProc)GetProcAddress(mmModule, wSoundBlasterMsg + 0x1e5);
    if (stopProc != 0) {
        err = stopProc();
        if (err != 0)
            WinPrintf("SBPro Error(musStopMusic)(%u)\n", err);
    }
    closeProc = (VoidProc)GetProcAddress(mmModule, wSoundBlasterMsg + 0x15b);
    if (closeProc != 0)
        closeProc();
    GlobalPageUnlock(mmPage);
    GlobalUnwire(mmHandle);
    GlobalFree(mmHandle);
    mmHandle = 0;
    mmPage = 0;
    mmStateWord = 0;
}
