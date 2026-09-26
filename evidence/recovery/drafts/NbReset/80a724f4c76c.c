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
};

void far NbReset(void)
{
    struct NetbiosControlBlock ncb = { 0 };
    unsigned char status;

    ncb.command = 0x32;
    NetBios(&ncb);
    DebugWinPrintf("NetBIOS reset");

    status = ncb.final_status;
    if (status < 0x50)
        DebugWinPrintf("NetBIOS reset status %u: %s", status,
                       (char far *)NB_RETCODE[status]);
    else if (ncb.final_status < 0xf0)
        DebugWinPrintf("NetBIOS reset status %u", status);
    else
        DebugWinPrintf("NetBIOS reset status %u: %s", status,
                       (char far *)NB_RETCODE[status]);
}
