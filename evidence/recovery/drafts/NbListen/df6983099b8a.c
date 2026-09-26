extern void *memset(void *, int, unsigned);
extern unsigned int far strlen(char far *s);
extern void far *far memcpy(void far *d, void far *s, unsigned int n);
/* Build a NetBIOS Listen NCB from the local and remote names. */
extern unsigned int far strlen(char far *s);
extern void far *far memcpy(void far *d, void far *s, unsigned int n);
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];

void far NbListen(char far *remote_name, char far *local_name,
                  unsigned char session, unsigned char number)
{
    unsigned char ncb[64];
    unsigned int length;
    memset(&ncb, 0, sizeof ncb);

    ncb[0] = 0x11;
    memset(ncb + 0x0a, 0x20, 16);
    length = strlen(remote_name);
    if (length > 16)
        length = 16;
    memcpy(ncb + 0x0a, remote_name, length);
    ncb[0x19] = 0;

    memset(ncb + 0x1a, 0x20, 16);
    length = strlen(local_name);
    if (length > 16)
        length = 16;
    memcpy(ncb + 0x1a, local_name, length);
    ncb[0x29] = 0;

    ncb[0x0e] = session;
    ncb[0x10] = number;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS listen");

    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS listen status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS listen status %u", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS listen status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
}
