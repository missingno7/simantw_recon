/*
 * IsMMMidiAvail resolves the Multimedia MIDI entry point named by the
 * module's private string table.  A non-null procedure address is invoked;
 * failure returns zero.  The module handle is the far state word observed at
 * the verified ES:0x8d08 location, while the name begins at DS:0x0afa.
 */
typedef void (far *MMProc)(void);
extern MMProc far pascal GetProcAddress(int handle, char far *name);
extern int far mmState[];
extern char near wSoundBlasterMsg[];

int IsMMMidiAvail(void)
{
    MMProc proc;

    proc = GetProcAddress(mmState[0x4684], wSoundBlasterMsg + 6);
    if (proc)
        return proc();
    return 0;
}
