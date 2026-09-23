/* Unit review (gr:7712): GetProcAddress returns the generic far procedure
 * pointer FARPROC (KERNEL.50); each caller converts it to its own procedure
 * type, so the members share one declaration in the unit. */
/* Named private module handle: selector BF78 resolves segment 8; original word at 8D08 is initialized zero. Full DATA and selector contribution proof required. */
/*
 * IsMMWaveAvail resolves the Multimedia wave entry point and returns its
 * result when present.  The wave name is the private string-table entry at
 * DS:0x0b0c; the handle table is shared with the MIDI availability probe.
 */
typedef int (far pascal *FARPROC)();
typedef int (far *MMProc)(void);
extern FARPROC far pascal GetProcAddress(int handle, char far *name);
static int __based(__segname("SIMANT_DATA_GROUP")) mmModule = 0;
extern char near wSoundBlasterMsg[];

int IsMMWaveAvail(void)
{
    MMProc proc;

    proc = (MMProc)GetProcAddress(mmModule, wSoundBlasterMsg + 0x18);
    if (proc)
        return proc();
    return 0;
}
