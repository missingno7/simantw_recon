/* NetBios Reset with a byte-addressed automatic 64-byte control block. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];
unsigned int far NbReset(void)
{
    unsigned char ncb[64];
    int i;
    for (i = 0; i < 64; ++i)
        ncb[i] = 0;
    ncb[0] = 0x32;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS reset");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS reset status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS reset status %u", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS reset status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
}
