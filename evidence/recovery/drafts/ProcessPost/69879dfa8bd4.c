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
    int result;
    unsigned int length;

    result = 0;
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
            result = 1;
            return result;
        }

        NbSend((unsigned char far *)&MapPlane, 2, completed.lsn);
        switch (MapPlane) {
        case 0:
        case 1:
            length = 0x1000;
            NbReceive(completed.lsn, MapA, &length);
            NbSend((unsigned char far *)&MapPlane, 2, completed.lsn);
            length = 0x1000;
            NbReceive(completed.lsn,
                      (unsigned char far *)((unsigned long)MapA + 0x1000L),
                      &length);
            NbSend((unsigned char far *)&MapPlane, 2, completed.lsn);
            length = 0x1000;
            NbReceive(completed.lsn, LifeA, &length);
            NbSend((unsigned char far *)&MapPlane, 2, completed.lsn);
            length = 0x1000;
            NbReceive(completed.lsn,
                      (unsigned char far *)((unsigned long)LifeA + 0x1000L),
                      &length);
            NbSend((unsigned char far *)&MapPlane, 2, completed.lsn);
            break;
        case 2:
            length = 0x1000;
            NbReceive(completed.lsn, MapB, &length);
            NbSend((unsigned char far *)&MapPlane, 2, completed.lsn);
            length = 0x1000;
            NbReceive(completed.lsn, LifeB, &length);
            NbSend((unsigned char far *)&MapPlane, 2, completed.lsn);
            break;
        case 3:
            length = 0x1000;
            NbReceive(completed.lsn, MapR, &length);
            NbSend((unsigned char far *)&MapPlane, 2, completed.lsn);
            length = 0x1000;
            NbReceive(completed.lsn, LifeR, &length);
            NbSend((unsigned char far *)&MapPlane, 2, completed.lsn);
            break;
        }

        NbSend(ForSaleState, DataBlockEnd - ForSaleState, completed.lsn);
        NbHangUp(completed.lsn);
        NbPostListen(processPostClientName, processPostServerName, 0x3c,
                     result, (void far *)NetBIOSPost);
        return result;

    case -106:
        if (completed.commandComplete == 10) {
            processPostState = 1;
            return result;
        }
        if (completed.commandComplete > 10) {
            NbFinalStatus((struct NetbiosControlBlock far *)localNCB);
            return result;
        }
        if (completed.commandComplete == 0 ||
            completed.commandComplete == 5) {
            NbPostReceiveAny((unsigned char)session,
                             (unsigned char far *)theNetBiosBuffer,
                             0x2000, (unsigned long)NetBIOSPost);
            return result;
        }
        NbFinalStatus((struct NetbiosControlBlock far *)localNCB);
        return result;
    }

    return result;
}
