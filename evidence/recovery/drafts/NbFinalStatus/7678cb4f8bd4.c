/* Probe the far-qualified return-message pointer used by the status report. */
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
    union StatusSlot { unsigned short whole; unsigned char value; } statusSlot;

    statusSlot.value = ncb->final_status;
    if (statusSlot.value < 0x50)
        DebugWinPrintf("NetBIOS final status %u: %s", statusSlot.value,
                       (char far *)NB_RETCODE[statusSlot.value]);
    else if (ncb->final_status < 0xf0)
        DebugWinPrintf("NetBIOS final status %u", statusSlot.value);
    else
        DebugWinPrintf("NetBIOS final status %u: %s", statusSlot.value,
                       (char far *)NB_RETCODE[statusSlot.value - 0xa0]);
}
