/* Process completed NetBIOS receive requests and repost the listener.  The
 * eight 4K DS buffers below are named only by their observed offsets until
 * their MAPSYM owners are established. */
struct NCB {
    char command;
    unsigned char retcode;
    unsigned char lsn;
    unsigned char num;
    unsigned int bufferOffset;
    unsigned int bufferSegment;
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

extern unsigned int far ncbTail;
extern unsigned int far ncbOffset[];
extern unsigned int far ncbSegment[];
extern char far * near theNetBiosBuffer;
extern int near MapPlane;
extern int near netBiosListenDone;
extern char near netBiosMessageBuffer28E8[4096];
extern char near netBiosMessageBuffer38E8[4096];
extern char near netBiosMessageBuffer48E8[4096];
extern char near netBiosMessageBuffer58E8[4096];
extern char near netBiosMessageBuffer68E8[4096];
extern char near netBiosMessageBuffer88E8[4096];
extern char near netBiosMessageBuffer98E8[4096];
extern char near netBiosStatusBufferAC5A[0x100];
extern void far movedata(unsigned int sourceSegment, unsigned int sourceOffset,
                         unsigned int destinationSegment, unsigned int destinationOffset,
                         unsigned int count);
extern int far NbFinalStatus(struct NCB far *ncb);
extern int far NbHangUp(unsigned char lsn);
extern int far NbSend();
extern int far NbReceive();
extern int far NbPostListen();
extern int far NbPostReceiveAny();

#define POST_OFF(p) ((unsigned int)(unsigned long)(void far *)(p))
#define POST_SEG(p) ((unsigned int)(((unsigned long)(void far *)(p)) >> 16))

int far ProcessPost(void)
{
    struct NCB completed;
    struct NCB far *localNCB;
    unsigned int index;
    unsigned int bytes;
    int result;
    char far *buffer;

    result = 0;
    localNCB = (struct NCB far *)&completed;
    index = ncbTail;
    movedata(ncbSegment[index], ncbOffset[index], POST_SEG(localNCB),
             POST_OFF(localNCB), 0x40);
    ncbTail++;
    if (ncbTail == 10)
        ncbTail = 0;

    switch (completed.command) {
    case -111:
        if (completed.commandComplete != 0) {
            NbFinalStatus(localNCB);
            NbHangUp(completed.lsn);
            result = 1;
            return result;
        }
        NbSend(completed.lsn, 2, (int far *)&MapPlane);
        if (MapPlane < 0)
            return result;
        switch (MapPlane) {
        case 0:
            buffer = netBiosMessageBuffer28E8;
            break;
        case 1:
            buffer = netBiosMessageBuffer38E8;
            break;
        case 2:
            buffer = netBiosMessageBuffer48E8;
            break;
        case 3:
            buffer = netBiosMessageBuffer58E8;
            break;
        case 4:
            buffer = netBiosMessageBuffer68E8;
            break;
        case 5:
            buffer = netBiosMessageBuffer88E8;
            break;
        case 6:
            buffer = netBiosMessageBuffer98E8;
            break;
        default:
            NbFinalStatus(localNCB);
            return result;
        }
        bytes = 0x1000;
        result = NbReceive(completed.lana, completed.lsn, buffer, &bytes);
        if (result == 0)
            NbSend(completed.lsn, 2, (int far *)buffer);
        NbPostListen(localNCB);
        return result;
    case -106:
        switch (completed.commandComplete) {
        case 10:
            result = NbPostReceiveAny((struct NCB far *)theNetBiosBuffer);
            if (result != 0)
                netBiosListenDone = 1;
            return result;
        case 0:
        case 5:
            bytes = 0x1000;
            buffer = netBiosStatusBufferAC5A;
            result = NbReceive(completed.lana, completed.lsn, buffer, &bytes);
            if (result == 0)
                NbSend(localNCB);
            return result;
        default:
            NbFinalStatus(localNCB);
            return result;
        }
    default:
        return result;
    }
}
