/* Build and submit a Send command block with its session, far buffer and
   requested byte count. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];

struct NetbiosControlBlock {
    unsigned char command;
    unsigned char immediate_status;
    unsigned char session;
    unsigned char reserved0;
    unsigned char far *buffer;
    unsigned int length;
    unsigned char reserved[0x27];
    unsigned char final_status;
    unsigned char tail[14];
};

void far NbSend(unsigned char far *buffer, unsigned int length,
                unsigned char session)
{
    struct NetbiosControlBlock ncb = { 0 };

    ncb.command = 0x14;
    ncb.session = session;
    ncb.buffer = buffer;
    ncb.length = length;
    NetBios(&ncb);
    DebugWinPrintf("NetBIOS send");

    if (ncb.final_status < 0x50)
        DebugWinPrintf("NetBIOS send status %u: %s", ncb.final_status,
                       (char far *)NB_RETCODE[ncb.final_status]);
    else if (ncb.final_status < 0xf0)
        DebugWinPrintf("NetBIOS send status %u", ncb.final_status);
    else
        DebugWinPrintf("NetBIOS send status %u: %s", ncb.final_status,
                       (char far *)NB_RETCODE[ncb.final_status]);
}
