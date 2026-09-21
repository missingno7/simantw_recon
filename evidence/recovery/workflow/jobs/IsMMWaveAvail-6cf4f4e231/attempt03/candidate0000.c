/* Named private module handle: selector BF78 resolves segment 8; original word at 8D08 is initialized zero. Full DATA and selector contribution proof required. */
/*
 * IsMMWaveAvail resolves the Multimedia wave entry point and returns its
 * result when present.  The wave name is the private string-table entry at
 * DS:0x0b0c; the handle table is shared with the MIDI availability probe.
 */
typedef int (far *MMProc)(void);
extern MMProc far pascal GetProcAddress(int handle, char far *name);
static int __based(__segname("SIMANT_DATA_GROUP")) mmModule = 0;
extern char near wSoundBlasterMsg[];

int IsMMWaveAvail(void)
{
    MMProc proc;

    proc = GetProcAddress(mmModule, wSoundBlasterMsg + 0x18);
    if (proc)
        return proc();
    return 0;
}
