/* Submit a Reset command block, emit the operation notice, and classify the
   returned NetBIOS status byte. */
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];

struct NetbiosControlBlock {
    unsigned char command;
    unsigned char immediate_status;
    unsigned char reserved[0x2f];
    unsigned char final_status;
    unsigned char tail[14];
};

void far NbReset(void)
{
    struct NetbiosControlBlock ncb = { 0 };
    ncb.command = 0x32;
    NetBios(&ncb);
    DebugWinPrintf("NetBIOS reset");

    if (ncb.final_status < 0x50)
        DebugWinPrintf("NetBIOS reset status %u: %s", ncb.final_status,
                       (char far *)NB_RETCODE[ncb.final_status]);
    else if (ncb.final_status < 0xf0)
        DebugWinPrintf("NetBIOS reset status %u", ncb.final_status);
    else
        DebugWinPrintf("NetBIOS reset status %u: %s", ncb.final_status,
                       (char far *)NB_RETCODE[ncb.final_status]);
}
