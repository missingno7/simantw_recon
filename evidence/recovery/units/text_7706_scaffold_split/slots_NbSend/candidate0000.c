extern void *memset(void *, int, unsigned);
/* Send with a byte-addressed local NCB and its original far buffer. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];
void far NbSend(unsigned char far *buffer, unsigned int length,
                unsigned char session)
{
    unsigned char ncb[64];
    memset(ncb, 0, 64);
    ncb[0] = 0x14;
    ncb[2] = session;
    *(unsigned char far **)&ncb[4] = buffer;
    *(unsigned int far *)&ncb[8] = length;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS: Send.\n");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): Adapter malfunction.\n", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
}
