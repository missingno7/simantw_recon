/* Candidate translation unit gr_7712_IsMMMidiAvail_3_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _IsMMMidiAvail, _IsMMWaveAvail
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

typedef int (far pascal *FARPROC)();
typedef int (far *MMProc)(void);
extern FARPROC far pascal GetProcAddress(int handle, char far *name);
static int __based(__segname("SIMANT_DATA_GROUP")) mmModule = 0;
extern char near wSoundBlasterMsg[];




int IsMMMidiAvail(void)
{
    MMProc proc;

    proc = (MMProc)GetProcAddress(mmModule, wSoundBlasterMsg + 6);
    if (proc)
        return proc();
    return 0;
}

int IsMMWaveAvail(void)
{
    MMProc proc;

    proc = (MMProc)GetProcAddress(mmModule, wSoundBlasterMsg + 0x18);
    if (proc)
        return proc();
    return 0;
}

