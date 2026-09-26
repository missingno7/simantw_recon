/* Process completed NetBIOS receive requests and repost the listener.  The
 * eight 4K DS buffers below are named only by their observed offsets until
 * their MAPSYM owners are established. */
struct NCB {
    unsigned char command;
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
extern int far NbSend(struct NCB far *ncb);
extern int far NbReceive(unsigned char lana, unsigned char lsn,
                         char far *buffer, unsigned int far *length);
extern int far NbPostListen(struct NCB far *ncb);
extern int far NbPostReceiveAny(struct NCB far *ncb);

#define POST_OFF(p) ((unsigned int)(unsigned long)(void far *)(p))
#define POST_SEG(p) ((unsigned int)(((unsigned long)(void far *)(p)) >> 16))

int far ProcessPost(void)
{
    struct NCB completed;
    unsigned int index;
    unsigned int bytes;
    int result;
    char far *buffer;

    index = ncbTail;
    movedata(ncbSegment[index], ncbOffset[index], POST_SEG(&completed),
             POST_OFF(&completed), 0x40);
    ncbTail++;
    if (ncbTail == 10)
        ncbTail = 0;

    if (completed.command == 0x91)
        return 0;
    if (completed.command == 0x96) {
        if (completed.commandComplete != 0) {
            NbFinalStatus(&completed);
            NbHangUp(completed.lsn);
            return 1;
        }
        NbSend(&completed);
        if (MapPlane < 0)
            return 0;
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
            NbFinalStatus(&completed);
            return 0;
        }
        bytes = 0x1000;
        result = NbReceive(completed.lana, completed.lsn, buffer, &bytes);
        if (result == 0)
            NbSend(&completed);
        NbPostListen(&completed);
        return result != 0;
    }
    if (completed.commandComplete != 0) {
        NbFinalStatus(&completed);
        NbHangUp(completed.lsn);
        return 1;
    }
    result = NbPostReceiveAny((struct NCB far *)theNetBiosBuffer);
    if (result != 0)
        netBiosListenDone = 1;
    return result;
}
