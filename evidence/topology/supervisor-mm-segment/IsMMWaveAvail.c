/* Expert hypothesis: declare the private module handle in its independently resolved named segment, without absolute indices or synthetic padding. */
/*
 * IsMMWaveAvail resolves the Multimedia wave entry point and returns its
 * result when present.  The wave name is the private string-table entry at
 * DS:0x0b0c; the handle table is shared with the MIDI availability probe.
 */
typedef int (far *MMProc)(void);
extern MMProc far pascal GetProcAddress(int handle, char far *name);
static int __based(__segname("SIMANT_DATA_GROUP")) mmModule;
extern char near wSoundBlasterMsg[];

int IsMMWaveAvail(void)
{
    MMProc proc;

    proc = GetProcAddress(mmModule, wSoundBlasterMsg + 0x18);
    if (proc)
        return proc();
    return 0;
}
