/* Build a NetBIOS Call NCB with space-padded calling names. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];

void far NbCall(char far *local_name, char far *remote_name,
                unsigned char session, unsigned char number)
{
    unsigned char ncb[64] = { 0 };
    int length;
    int i;

    ncb[0] = 0x10;
    for (i = 0; i < 16; ++i)
        ncb[0x0a + i] = 0x20;
    length = 0;
    while (remote_name[length] != 0)
        ++length;
    if (length > 16)
        length = 16;
    for (i = 0; i < length; ++i)
        ncb[0x0a + i] = remote_name[i];
    ncb[0x19] = 0;

    for (i = 0; i < 16; ++i)
        ncb[0x1a + i] = 0x20;
    length = 0;
    while (local_name[length] != 0)
        ++length;
    if (length > 16)
        length = 16;
    for (i = 0; i < length; ++i)
        ncb[0x1a + i] = local_name[i];
    ncb[0x29] = 0;

    ncb[0x0e] = session;
    ncb[0x10] = number;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS call");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS call status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS call status %u", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS call status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
}
