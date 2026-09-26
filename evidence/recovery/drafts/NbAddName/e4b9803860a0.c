/* Put the requested name into a space-padded Add Name command block, submit
   it, then return the name number assigned by NetBIOS. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];

void far NbAddName(char far *name)
{
    unsigned char ncb[64] = { 0 };
    int length;
    int i;

    ncb[0] = 0x30;
    for (i = 0; i < 16; ++i)
        ncb[0x1a + i] = 0x20;

    length = 0;
    while (name[length] != 0)
        ++length;
    if (length > 16)
        length = 16;
    for (i = 0; i < length; ++i)
        ncb[0x1a + i] = name[i];
    ncb[0x29] = 0;

    NetBios(ncb);
    DebugWinPrintf("NetBIOS add name");

    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS add-name status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS add-name status %u", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS add-name status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);

    return ncb[3];
}
