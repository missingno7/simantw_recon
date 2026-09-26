/* Zero an NCB through the MSC recognized memset intrinsic, then submit it. */
extern void *memset(void *, int, unsigned);
extern void far NetBios(unsigned char far *);
extern void far DebugWinPrintf(char far *format, ...);
int NbCheck(void)
{
    unsigned char ncb[64];
    memset(ncb, 0, 64);
    ncb[0] = 0x7f;
    NetBios((unsigned char far *)ncb);
    if (ncb[0x31] != 3) {
        DebugWinPrintf("NetBIOS not loaded (No response from Int5C).\n");
        return 0;
    }
    return 1;
}
