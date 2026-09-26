/* Report a completed NetBIOS control block using its final return byte and
   the recorded 60-byte return-message table. */
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];
struct NetbiosControlBlock {
    unsigned char command;
    unsigned char immediate_status;
    unsigned char reserved[0x2f];
    unsigned char final_status;
};

void far NbFinalStatus(struct NetbiosControlBlock far *ncb)
{
    unsigned char status;

    status = ncb->final_status;
    if (status < 0x50)
        DebugWinPrintf("NetBIOS final status %u: %s", status,
                       NB_RETCODE[status]);
    else if (ncb->final_status < 0xf0)
        DebugWinPrintf("NetBIOS final status %u", status);
    else
        DebugWinPrintf("NetBIOS final status %u: %s", status,
                       NB_RETCODE[status]);
}
