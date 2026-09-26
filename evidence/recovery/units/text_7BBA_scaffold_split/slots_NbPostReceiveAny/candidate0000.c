extern void *memset(void *, int, unsigned);
/* Reuse the shared 64-byte NetBIOS control block for Post Receive Any, passing
   the caller's buffer, capacity and timeout through the corresponding fields. */
static unsigned char near postReceiveNcb[64];

extern void far NetBios(unsigned char far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];

unsigned int far NbPostReceiveAny(unsigned char session,
                                  unsigned char far *buffer,
                                  unsigned int length,
                                  unsigned long timeout)
{
    memset(postReceiveNcb, 0, 64);

    postReceiveNcb[0] = 0x96;
    postReceiveNcb[3] = session;
    *(unsigned char far **)&postReceiveNcb[4] = buffer;
    *(unsigned int far *)&postReceiveNcb[8] = length;
    *(unsigned long far *)&postReceiveNcb[0x2c] = timeout;
    NetBios(postReceiveNcb);
    DebugWinPrintf("NetBIOS: PostReceiveAny.\n");

    if (postReceiveNcb[1] < 0x50)
        DebugWinPrintf("NetBIOS RetCode(%#x): %s\n", postReceiveNcb[1],
                       (char far *)NB_RETCODE[postReceiveNcb[1]]);
    else if (postReceiveNcb[1] < 0xf0)
        DebugWinPrintf("NetBIOS RetCode(%#x): Adapter malfunction.\n", postReceiveNcb[1]);
    else
        DebugWinPrintf("NetBIOS RetCode(%#x): %s\n", postReceiveNcb[1],
                       (char far *)NB_RETCODE[postReceiveNcb[1] - 0xa0]);

    return postReceiveNcb[1];
}
