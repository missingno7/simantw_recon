extern void *memset(void *, int, unsigned);
extern unsigned strlen(const char far *);
extern void far *far memcpy(void far *d, void far *s, unsigned int n);
/* Build a NetBIOS Call NCB with space-padded calling names. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];

unsigned char far NbCall(char far *local_name, char far *remote_name,
                unsigned char session, unsigned char number)
{
    unsigned char ncb[64];
    int length;
    int i;

    memset(ncb, 0, 64);
    ncb[0] = 0x10;
    memset(&ncb[0x0a], 0x20, 16);
    length = strlen(remote_name);
    if (length > 16)
        length = 16;
    memcpy(&ncb[0x0a], remote_name, length);
    ncb[0x19] = 0;

    memset(&ncb[0x1a], 0x20, 16);
    length = strlen(local_name);
    if (length > 16)
        length = 16;
    memcpy(&ncb[0x1a], local_name, length);
    ncb[0x29] = 0;

    ncb[0x2a] = session;
    ncb[0x2b] = number;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS: Call.\n");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): Adapter malfunction.\n", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
    if (ncb[0x31] == 0)
        return ncb[2];
    return 0;
}
