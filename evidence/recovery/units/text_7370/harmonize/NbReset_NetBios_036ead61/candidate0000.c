extern void *memset(void *, int, unsigned);
/* NetBios Reset with a byte-addressed automatic 64-byte control block. */
extern void far NetBios(unsigned char far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];
unsigned int far NbReset(void)
{
    unsigned char ncb[64];
    memset(ncb, 0, 64);
    ncb[0] = 0x32;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS: Reset.\n");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): Adapter malfunction.\n", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
}
