extern void *memset(void *, int, unsigned);
/* Hang Up with a byte-addressed local NCB and the session at byte two. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];
void far NbHangUp(unsigned char session)
{
    unsigned char ncb[64];
    memset(ncb, 0, 64);
    ncb[0] = 0x12;
    ncb[2] = session;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS hang up");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS hang up status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS hang up status %u", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS hang up status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
}
