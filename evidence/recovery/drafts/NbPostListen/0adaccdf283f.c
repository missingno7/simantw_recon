extern void *memset(void *, int, unsigned);
extern unsigned int far strlen(char far *s);
extern void far *far memcpy(void far *d, void far *s, unsigned int n);
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
    int length;
    unsigned int status;

    memset(edata + 0x112, 0, 0x40);
    edata[0x112] = 0x91;

    memset(edata + 0x11c, 0x20, 16);
    length = strlen(call_name);
    if (length > 16)
        length = 16;
    memcpy(edata + 0x11c, call_name, length);
    edata[0x12b] = 0;

    memset(edata + 0x12c, 0x20, 16);
    length = strlen(name);
    if (length > 16)
        length = 16;
    memcpy(edata + 0x12c, name, length);
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
