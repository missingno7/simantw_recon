struct NCB {
    char command;
    unsigned char retcode;
    unsigned char lsn;
    unsigned char number;
    void far *buffer;
    unsigned int length;
    char callName[16];
    char name[16];
    unsigned char receiveTimeout;
    unsigned char sendTimeout;
    void (far *post)(void);
    unsigned char lana;
    unsigned char commandComplete;
    unsigned char reserved[14];
};

struct NetbiosControlBlock {
    unsigned char command;
    unsigned char immediateStatus;
    unsigned char reserved[0x2f];
    unsigned char finalStatus;
};

extern unsigned int far ncbTail;
extern unsigned int far ncbOffset[];
extern unsigned int far ncbSegment[];
extern int near MapPlane;
extern char far * near theNetBiosBuffer;
extern char near processPostServerName[8];
extern char near processPostClientName[8];
extern int near processPostState;

extern unsigned char near MapA[128][64];
extern unsigned char near MapB[128][64];
extern unsigned char near MapR[128][64];
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[128][64];
extern unsigned char near LifeR[128][64];
extern unsigned char near ForSaleState[];
extern unsigned char near DataBlockEnd[];

extern void far movedata(unsigned int sourceSegment,
                         unsigned int sourceOffset,
                         unsigned int destinationSegment,
                         unsigned int destinationOffset,
                         unsigned int count);
extern volatile void far NbFinalStatus(
    volatile struct NetbiosControlBlock far *ncb);
extern int far NbHangUp(char session);
extern int far NbSend(unsigned char far *buffer, int length, char session);
extern unsigned int far NbReceive(unsigned char session,
                                  unsigned char far *buffer,
                                  unsigned int far *length);
extern unsigned int far NbPostListen(char far *name, char far *callName,
                                     unsigned char session,
                                     unsigned char number,
                                     void far *post);
extern unsigned int far NbPostReceiveAny(unsigned char session,
                                         unsigned char far *buffer,
                                         unsigned int length,
                                         unsigned long timeout);
extern void interrupt far NetBIOSPost(unsigned int segment,
                                      unsigned int savedDS,
                                      unsigned int savedDI,
                                      unsigned int savedSI,
                                      unsigned int savedBP,
                                      unsigned int savedSP,
                                      unsigned int offset);

#define POST_OFF(p) ((unsigned int)(unsigned long)(void far *)(p))
#define POST_SEG(p) ((unsigned int)(((unsigned long)(void far *)(p)) >> 16))

int far ProcessPost(char session)
{
    struct NCB completed;
    struct NCB far *localNCB;
    struct { int reply; unsigned int length; } buffers;
    int returnStatus = 0;

    localNCB = (struct NCB far *)&completed;
    movedata(ncbSegment[ncbTail], ncbOffset[ncbTail], POST_SEG(localNCB),
             POST_OFF(localNCB), 0x40);
    ncbTail++;
    if (ncbTail == 10)
        ncbTail = 0;

    switch (completed.command) {
    case -111:
        if (completed.commandComplete != 0) {
            NbFinalStatus((struct NetbiosControlBlock far *)localNCB);
            NbHangUp(completed.lsn);
            returnStatus = 1;
            goto processPostExit;
        }

        NbSend((unsigned char far *)&MapPlane, 2, completed.lsn);
        switch (MapPlane) {
        case 0:
        case 1:
            buffers.length = 0x1000;
            NbReceive(completed.lsn, MapA, &buffers.length);
            NbSend((unsigned char far *)&buffers.reply, 2, completed.lsn);
            buffers.length = 0x1000;
            NbReceive(completed.lsn,
                      (unsigned char far *)((unsigned long)MapA + 0x1000L),
                      &buffers.length);
            NbSend((unsigned char far *)&buffers.reply, 2, completed.lsn);
            buffers.length = 0x1000;
            NbReceive(completed.lsn, LifeA, &buffers.length);
            NbSend((unsigned char far *)&buffers.reply, 2, completed.lsn);
            buffers.length = 0x1000;
            NbReceive(completed.lsn,
                      (unsigned char far *)((unsigned long)LifeA + 0x1000L),
                      &buffers.length);
            NbSend((unsigned char far *)&buffers.reply, 2, completed.lsn);
            break;
        case 2:
            buffers.length = 0x1000;
            NbReceive(completed.lsn, MapB, &buffers.length);
            NbSend((unsigned char far *)&buffers.reply, 2, completed.lsn);
            buffers.length = 0x1000;
            NbReceive(completed.lsn, LifeB, &buffers.length);
            NbSend((unsigned char far *)&buffers.reply, 2, completed.lsn);
            break;
        case 3:
            buffers.length = 0x1000;
            NbReceive(completed.lsn, MapR, &buffers.length);
            NbSend((unsigned char far *)&buffers.reply, 2, completed.lsn);
            buffers.length = 0x1000;
            NbReceive(completed.lsn, LifeR, &buffers.length);
            NbSend((unsigned char far *)&buffers.reply, 2, completed.lsn);
            break;
        }

        NbSend(ForSaleState, DataBlockEnd - ForSaleState, completed.lsn);
        NbHangUp(completed.lsn);
        NbPostListen(processPostClientName, processPostServerName, 0x3c,
                     0, (void far *)NetBIOSPost);
        goto processPostExit;

    case -106:
        switch (completed.commandComplete) {
        case 10:
            processPostState = 1;
            goto processPostExit;
        case 0:
        case 5:
            NbPostReceiveAny((unsigned char)session,
                             (unsigned char far *)theNetBiosBuffer,
                             0x2000, (unsigned long)NetBIOSPost);
            goto processPostExit;
        default:
            NbFinalStatus((struct NetbiosControlBlock far *)localNCB);
            goto processPostExit;
        }
    }

processPostExit:
    return returnStatus;
}
