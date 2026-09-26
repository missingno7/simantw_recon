/* Set up the shared NCB for an asynchronous listen. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern unsigned char near edata[];
extern char near left_wedge[];
extern unsigned char far Dx8[];

void far NbPostListen(char far *name, char far *call_name,
                      unsigned char session, unsigned char number,
                      void far *buffer)
{
    int i;
    int length;
    unsigned int status;

    for (i = 0; i < 64; ++i)
        edata[0x112 + i] = 0;
    edata[0x112] = 0x91;

    for (i = 0; i < 16; ++i)
        edata[0x11c + i] = 0x20;
    length = 0;
    while (call_name[length] != 0)
        ++length;
    if (length > 16)
        length = 16;
    for (i = 0; i < length; ++i)
        edata[0x11c + i] = call_name[i];
    edata[0x12b] = 0;

    for (i = 0; i < 16; ++i)
        edata[0x12c + i] = 0x20;
    length = 0;
    while (name[length] != 0)
        ++length;
    if (length > 16)
        length = 16;
    for (i = 0; i < length; ++i)
        edata[0x12c + i] = name[i];
    edata[0x13b] = 0;

    edata[0x13c] = session;
    edata[0x13d] = number;
    *(void far * far *)(edata + 0x13e) = buffer;
    NetBios((void far *)(edata + 0x112));
    DebugWinPrintf((char far *)(left_wedge + 0x26e),
                   (char far *)(edata + 0x11c));

    status = edata[0x113];
    if (status < 0x50)
        DebugWinPrintf((char far *)(left_wedge + 0x1b4), status,
                       Dx8 + 0xa7f0 + status * 60);
    else if (status < 0xf0)
        DebugWinPrintf((char far *)(left_wedge + 0x1ce), status);
    else
        DebugWinPrintf((char far *)(left_wedge + 0x1fa), status,
                       Dx8 + 0x8270 + status * 60);
}
