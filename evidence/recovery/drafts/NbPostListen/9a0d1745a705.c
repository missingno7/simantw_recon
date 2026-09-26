extern void *memset(void *, int, unsigned);
extern unsigned int far strlen(char far *s);
extern void far *far memcpy(void far *d, void far *s, unsigned int n);
/* Set up the shared NCB for an asynchronous listen. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern unsigned char near edata[];
extern char near left_wedge[];
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];

unsigned char far NbPostListen(char far *name, char far *call_name,
                      unsigned char session, unsigned char number,
                      void far *buffer)
{
    int length;

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

    if (edata[0x113] < 0x50)
        DebugWinPrintf((char far *)(left_wedge + 0x1b4), edata[0x113],
                       (char far *)NB_RETCODE[edata[0x113]]);
    else if (edata[0x113] < 0xf0)
        DebugWinPrintf((char far *)(left_wedge + 0x1ce), edata[0x113]);
    else
        DebugWinPrintf((char far *)(left_wedge + 0x1fa), edata[0x113],
                       (char far *)NB_RETCODE[edata[0x113] - 0xa0]);
    return edata[0x113];
}
