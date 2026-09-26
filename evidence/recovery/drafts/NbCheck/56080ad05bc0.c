/* Initialize and submit an NCB; report a missing NetBIOS responder. */
extern void near NetBios(unsigned char far *);
extern int far DebugWinPrintf(char far *, ...);
int NbCheck(void)
{
    unsigned char ncb[64] = { 0 };
    ncb[0] = 0x7f;
    NetBios((unsigned char far *)ncb);
    if (ncb[0x31] != 3) {
        DebugWinPrintf("NetBIOS not loaded (No response from Int5C).\n");
        return 0;
    }
    return 1;
}
