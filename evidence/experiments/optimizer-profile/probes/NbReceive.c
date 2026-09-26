/* Submit a Receive command with the caller's buffer and current length, then
   copy the length returned in the command block back to the caller. */
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

unsigned int far NbReceive(unsigned char session,
                           unsigned char far *buffer,
                           unsigned int far *length)
{
    struct NetbiosControlBlock ncb;
    unsigned char near *p;

    for (p = (unsigned char near *)&ncb; p < (unsigned char near *)&ncb + 64; ++p)
        *p = 0;
    ncb.command = 0x15;
    ncb.session = session;
    ncb.buffer = buffer;
    ncb.length = *length;
    NetBios(&ncb);
    DebugWinPrintf("NetBIOS receive");

    if (ncb.final_status < 0x50)
        DebugWinPrintf("NetBIOS receive status %u: %s", ncb.final_status,
                       (char far *)NB_RETCODE[ncb.final_status]);
    else if (ncb.final_status < 0xf0)
        DebugWinPrintf("NetBIOS receive status %u", ncb.final_status);
    else
        DebugWinPrintf("NetBIOS receive status %u: %s", ncb.final_status,
                       (char far *)NB_RETCODE[ncb.final_status]);

    *length = ncb.length;
    return ncb.final_status;
}
