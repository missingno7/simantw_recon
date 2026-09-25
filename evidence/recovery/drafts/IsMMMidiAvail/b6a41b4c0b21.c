/* Named private module handle: selector BF78 resolves segment 8; original word at 8D08 is initialized zero. Full DATA and selector contribution proof required. */
/*
 * IsMMMidiAvail resolves the Multimedia MIDI entry point named by the
 * module's private string table.  A non-null procedure address is invoked;
 * failure returns zero.  The module handle is the far state word observed at
 * the verified ES:0x8d08 location, while the name begins at DS:0x0afa.
 */
typedef int (far *MMProc)(void);
extern MMProc far pascal GetProcAddress(int handle, char far *name);
static int __based(__segname("SIMANT_DATA_GROUP")) mmModule = 0;
extern char near wSoundBlasterMsg[];

int IsMMMidiAvail(void)
{
    MMProc proc;

    proc = GetProcAddress(mmModule, wSoundBlasterMsg + 6);
    if (proc)
        return proc();
    return 0;
}
