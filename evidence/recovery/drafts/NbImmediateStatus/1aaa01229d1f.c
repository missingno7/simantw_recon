/* Report the immediate NetBIOS return byte and use the return-message table
   for status values outside the command-pending range. */
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];
struct NetbiosControlBlock {
    unsigned char command;
    unsigned char immediate_status;
    unsigned char reserved[0x2f];
    unsigned char final_status;
};

void far NbImmediateStatus(struct NetbiosControlBlock far *ncb)
{
    unsigned char status;

    status = ncb->immediate_status;
    if (status < 0x50)
        DebugWinPrintf("NetBIOS immediate status %u: %s", status,
                       (char far *)NB_RETCODE[status]);
    else if (ncb->immediate_status < 0xf0)
        DebugWinPrintf("NetBIOS immediate status %u", status);
    else
        DebugWinPrintf("NetBIOS immediate status %u: %s", status,
                       (char far *)NB_RETCODE[status]);
}
