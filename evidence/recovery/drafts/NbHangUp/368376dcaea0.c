/* Submit a Hang Up command block and report its returned NetBIOS status. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];

struct NetbiosControlBlock {
    unsigned char command;
    unsigned char immediate_status;
    unsigned char session;
    unsigned char reserved[0x2e];
    unsigned char final_status;
    unsigned char tail[14];
};

void far NbHangUp(unsigned char session)
{
    struct NetbiosControlBlock ncb = { 0 };

    ncb.command = 0x12;
    ncb.session = session;
    NetBios(&ncb);
    DebugWinPrintf("NetBIOS hang up");

    if (ncb.final_status < 0x50)
        DebugWinPrintf("NetBIOS hang up status %u: %s", ncb.final_status,
                       (char far *)NB_RETCODE[ncb.final_status]);
    else if (ncb.final_status < 0xf0)
        DebugWinPrintf("NetBIOS hang up status %u", ncb.final_status);
    else
        DebugWinPrintf("NetBIOS hang up status %u: %s", ncb.final_status,
                       (char far *)NB_RETCODE[ncb.final_status]);
}
