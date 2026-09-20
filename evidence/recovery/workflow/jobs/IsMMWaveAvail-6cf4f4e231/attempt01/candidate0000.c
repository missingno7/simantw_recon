/*
 * IsMMWaveAvail resolves the Multimedia wave entry point and returns its
 * result when present.  The wave name is the private string-table entry at
 * DS:0x0b0c; the handle table is shared with the MIDI availability probe.
 */
typedef int (far *MMProc)(void);
extern MMProc far pascal GetProcAddress(int handle, char far *name);
extern int far mmState[];
extern char near wSoundBlasterMsg[];

int IsMMWaveAvail(void)
{
    MMProc proc;

    proc = GetProcAddress(mmState[0x4684], wSoundBlasterMsg + 0x18);
    if (proc)
        return proc();
    return 0;
}
