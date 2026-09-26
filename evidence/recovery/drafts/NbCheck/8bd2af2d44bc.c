/* Zero an NCB, submit it, and report the missing NetBIOS responder. */
extern void far NetBios(unsigned char far *);
extern int far DebugWinPrintf(char far *, ...);
int NbCheck(void)
{
    unsigned char ncb[64];
    unsigned i;
    for (i = 0; i < 64; ++i)
        ncb[i] = 0;
    ncb[0] = 0x7f;
    NetBios((unsigned char far *)ncb);
    if (ncb[0x31] != 3) {
        DebugWinPrintf("NetBIOS not loaded (No response from Int5C).\n");
        return 0;
    }
    return 1;
}
