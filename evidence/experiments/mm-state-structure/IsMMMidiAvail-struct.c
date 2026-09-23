typedef int (far *MMProc)(void);
extern MMProc far pascal GetProcAddress(int handle, char far *name);
extern char near wSoundBlasterMsg[];

struct MMStateProbe {
    int module;
    int soundInstalled;
    int waveInstalled;
    int midiHandle;
    int state08;
    int state0A;
    int waveHandle;
    int state0E;
    int state10;
    int refCount;
};
static struct MMStateProbe __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};

int IsMMMidiAvail(void)
{
    MMProc proc;
    proc = GetProcAddress(mmState.module, wSoundBlasterMsg + 6);
    if (proc)
        return proc();
    return 0;
}
