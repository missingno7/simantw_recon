extern void *memset(void *, int, unsigned);
extern unsigned int far strlen(char far *s);
extern void far *far memcpy(void far *d, void far *s, unsigned int n);
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
    struct NetbiosControlBlock ncb[2];

    memset(&ncb[0], 0, sizeof ncb[0]);
    ncb[0].command = 0x15;
    ncb[0].session = session;
    ncb[0].buffer = buffer;
    ncb[0].length = *length;
    NetBios(&ncb[0]);
    DebugWinPrintf("NetBIOS receive");

    if (ncb[0].final_status < 0x50)
        DebugWinPrintf("NetBIOS receive status %u: %s", ncb[0].final_status,
                       (char far *)NB_RETCODE[ncb[0].final_status]);
    else if (ncb[0].final_status < 0xf0)
        DebugWinPrintf("NetBIOS receive status %u", ncb[0].final_status);
    else
        DebugWinPrintf("NetBIOS receive status %u: %s", ncb[0].final_status,
                       (char far *)NB_RETCODE[ncb[0].final_status - 0xa0]);

    *length = ncb[0].length;
    return ncb[0].final_status;
}
