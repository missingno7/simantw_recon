extern void *memset(void *, int, unsigned);
extern unsigned int far strlen(char far *s);
extern void far *far memcpy(void far *d, void far *s, unsigned int n);
/* Put the requested name into a space-padded Delete Name command block, submit
   it, then return the name number assigned by NetBIOS. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];

void far NbDeleteName(char far *name)
{
    unsigned char ncb[64];
    int length;
    memset(&ncb, 0, sizeof ncb);

    ncb[0] = 0x31;
    memset(ncb + 0x1a, 0x20, 16);

    length = strlen(name);
    if (length > 16)
        length = 16;
    memcpy(ncb + 0x1a, name, length);
    ncb[0x29] = 0;

    NetBios(ncb);
    DebugWinPrintf("NetBIOS delete name");

    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS delete-name status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS delete-name status %u", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS delete-name status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);

}
