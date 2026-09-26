/* Candidate translation unit text_7370: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _NbFinalStatus, _NbImmediateStatus, _CopyName, _NbCall, _NbAddName, _NbReset, _NbSend, _NbListen, _NbPostListen, _NbDeleteName, _NbReceive, _NbPostReceiveAny, _NbHangUp, _NbCheck */

extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];
struct NetbiosControlBlock {
    unsigned char command;
    unsigned char immediate_status;
    unsigned char reserved[0x2f];
    unsigned char final_status;
};
static char nbFinalFormatLow[] = "NetBIOS Final RetCode(%#x): %s\n";
static char nbFinalAdapter[] = "NetBIOS Final RetCode(%#x): Adapter malfunction.\n";
static char nbFinalFormatHigh[] = "NetBIOS Final RetCode(%#x): %s\n";
static char nbImmediateFormatLow[] = "NetBIOS RetCode(%#x): %s\n";
static char nbImmediateAdapter[] = "NetBIOS RetCode(%#x): Adapter malfunction.\n";
static char nbImmediateFormatHigh[] = "NetBIOS RetCode(%#x): %s\n";
void far NbFinalStatus(struct NetbiosControlBlock far *ncb)
{
    union StatusSlot { unsigned short whole; unsigned char value; } statusSlot;

    statusSlot.value = ncb->final_status;
    if (statusSlot.value < 0x50)
        DebugWinPrintf(nbFinalFormatLow, statusSlot.value,
                       (char far *)NB_RETCODE[statusSlot.value]);
    else if (ncb->final_status < 0xf0)
        DebugWinPrintf(nbFinalAdapter, statusSlot.value);
    else
        DebugWinPrintf(nbFinalFormatHigh, statusSlot.value,
                       (char far *)NB_RETCODE[statusSlot.value - 0xa0]);
}

void far NbImmediateStatus(struct NetbiosControlBlock far *ncb)
{
    union StatusSlot { unsigned short whole; unsigned char value; } statusSlot;

    statusSlot.value = ncb->immediate_status;
    if (statusSlot.value < 0x50)
        DebugWinPrintf(nbImmediateFormatLow, statusSlot.value,
                       (char far *)NB_RETCODE[statusSlot.value]);
    else if (ncb->immediate_status < 0xf0)
        DebugWinPrintf(nbImmediateAdapter, statusSlot.value);
    else
        DebugWinPrintf(nbImmediateFormatHigh, statusSlot.value,
                       (char far *)NB_RETCODE[statusSlot.value - 0xa0]);
}

extern void *memset(void *, int, unsigned);
void CopyName(char far *destination, const char far *source)
{
    int length;
    memset(destination, ' ', 16);
    length = strlen(source);
    if (length > 16)
        length = 16;
    memcpy(destination, source, length);
    destination[15] = 0;
}

unsigned char far NbCall(char far *local_name, char far *remote_name,
                unsigned char session, unsigned char number)
{
    unsigned char ncb[64];
    int length;
    int i;

    memset(ncb, 0, 64);
    ncb[0] = 0x10;
    memset(&ncb[0x0a], 0x20, 16);
    length = strlen(remote_name);
    if (length > 16)
        length = 16;
    memcpy(&ncb[0x0a], remote_name, length);
    ncb[0x19] = 0;

    memset(&ncb[0x1a], 0x20, 16);
    length = strlen(local_name);
    if (length > 16)
        length = 16;
    memcpy(&ncb[0x1a], local_name, length);
    ncb[0x29] = 0;

    ncb[0x2a] = session;
    ncb[0x2b] = number;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS: Call.\n");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf(nbFinalFormatLow, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf(nbFinalAdapter, ncb[0x31]);
    else
        DebugWinPrintf(nbFinalFormatHigh, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
    if (ncb[0x31] == 0)
        return ncb[2];
    return 0;
}

unsigned char far NbAddName(char far *name)
{
    unsigned char ncb[64];
    int length;
    memset(&ncb, 0, sizeof ncb);

    ncb[0] = 0x30;
    memset(ncb + 0x1a, 0x20, 16);

    length = strlen(name);
    if (length > 16)
        length = 16;
    memcpy(ncb + 0x1a, name, length);
    ncb[0x29] = 0;

    NetBios(ncb);
    DebugWinPrintf("NetBIOS: AddName.\n");

    if (ncb[0x31] < 0x50)
        DebugWinPrintf(nbFinalFormatLow, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf(nbFinalAdapter, ncb[0x31]);
    else
        DebugWinPrintf(nbFinalFormatHigh, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);

    return ncb[3];
}

unsigned int far NbReset(void)
{
    unsigned char ncb[64];
    memset(ncb, 0, 64);
    ncb[0] = 0x32;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS: Reset.\n");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf(nbFinalFormatLow, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf(nbFinalAdapter, ncb[0x31]);
    else
        DebugWinPrintf(nbFinalFormatHigh, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
}

void far NbSend(unsigned char far *buffer, unsigned int length,
                unsigned char session)
{
    unsigned char ncb[64];
    memset(ncb, 0, 64);
    ncb[0] = 0x14;
    ncb[2] = session;
    *(unsigned char far **)&ncb[4] = buffer;
    *(unsigned int far *)&ncb[8] = length;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS: Send.\n");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf(nbFinalFormatLow, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf(nbFinalAdapter, ncb[0x31]);
    else
        DebugWinPrintf(nbFinalFormatHigh, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
}

extern char far *far strcpy(char far *dest, char far *src);
unsigned char far NbListen(char far *name, char far *call_name,
                  unsigned char session, unsigned char number)
{
    unsigned char ncb[64];
    int length;
    memset(&ncb, 0, sizeof ncb);

    ncb[0] = 0x11;
    memset(ncb + 0x0a, 0x20, 16);
    length = strlen(call_name);
    if (length > 16)
        length = 16;
    memcpy(ncb + 0x0a, call_name, length);
    ncb[0x19] = 0;

    memset(ncb + 0x1a, 0x20, 16);
    length = strlen(name);
    if (length > 16)
        length = 16;
    memcpy(ncb + 0x1a, name, length);
    ncb[0x29] = 0;

    ncb[0x2a] = session;
    ncb[0x2b] = number;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS: Listen(%s).\n", (char far *)(ncb + 0x0a));

    if (ncb[0x31] < 0x50)
        DebugWinPrintf(nbFinalFormatLow, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf(nbFinalAdapter, ncb[0x31]);
    else
        DebugWinPrintf(nbFinalFormatHigh, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
    if (call_name[0] == '*')
        strcpy(call_name, (char far *)(ncb + 0x0a));

    return ncb[2];
}

extern unsigned char near edata[];
extern char near left_wedge[];
unsigned int far NbPostListen(char far *name, char far *call_name,
                      unsigned char session, unsigned char number,
                      void far *buffer)
{
    int length;

    memset(edata + 0x112, 0, 0x40);
    edata[0x112] = 0x91;

    memset(edata + 0x11c, 0x20, 16);
    length = strlen(call_name);
    if (length > 16)
        length = 16;
    memcpy(edata + 0x11c, call_name, length);
    edata[0x12b] = 0;

    memset(edata + 0x12c, 0x20, 16);
    length = strlen(name);
    if (length > 16)
        length = 16;
    memcpy(edata + 0x12c, name, length);
    edata[0x13b] = 0;

    edata[0x13c] = session;
    edata[0x13d] = number;
    *(void far * far *)(edata + 0x13e) = buffer;
    NetBios((void far *)(edata + 0x112));
    DebugWinPrintf("NetBIOS: PostListen(%s).\n",
                   (char far *)(edata + 0x11c));

    if (edata[0x113] < 0x50)
        DebugWinPrintf(nbImmediateFormatLow, edata[0x113],
                       (char far *)NB_RETCODE[edata[0x113]]);
    else if (edata[0x113] < 0xf0)
        DebugWinPrintf(nbImmediateAdapter, edata[0x113]);
    else
        DebugWinPrintf(nbImmediateFormatHigh, edata[0x113],
                       (char far *)NB_RETCODE[edata[0x113] - 0xa0]);
    return edata[0x113];
}

void far NbDeleteName(char far *name)
{
    unsigned char ncb[64];
    int length;
    memset(&ncb, 0, sizeof ncb);

    ncb[0] = 0x31;
    memset(ncb + 0x1a, 0x20, 16);

    length = strlen(name);
    if (length > 16)
        length = 16;
    memcpy(ncb + 0x1a, name, length);
    ncb[0x29] = 0;

    NetBios(ncb);
    DebugWinPrintf("NetBIOS: Delete Name.\n");

    if (ncb[0x31] < 0x50)
        DebugWinPrintf(nbFinalFormatLow, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf(nbFinalAdapter, ncb[0x31]);
    else
        DebugWinPrintf(nbFinalFormatHigh, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);

}

struct NetbiosControlBlock_2 {
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
    struct NetbiosControlBlock_2 ncb[2];

    memset(&ncb[0], 0, sizeof ncb[0]);
    ncb[0].command = 0x15;
    ncb[0].session = session;
    ncb[0].buffer = buffer;
    ncb[0].length = *length;
    NetBios(&ncb[0]);
    DebugWinPrintf("NetBIOS: Receive.\n");

    if (ncb[0].final_status < 0x50)
        DebugWinPrintf(nbFinalFormatLow, ncb[0].final_status,
                       (char far *)NB_RETCODE[ncb[0].final_status]);
    else if (ncb[0].final_status < 0xf0)
        DebugWinPrintf(nbFinalAdapter, ncb[0].final_status);
    else
        DebugWinPrintf(nbFinalFormatHigh, ncb[0].final_status,
                       (char far *)NB_RETCODE[ncb[0].final_status - 0xa0]);

    *length = ncb[0].length;
    return ncb[0].final_status;
}

static unsigned char near postReceiveNcb[64];
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
        DebugWinPrintf(nbImmediateFormatLow, postReceiveNcb[1],
                       (char far *)NB_RETCODE[postReceiveNcb[1]]);
    else if (postReceiveNcb[1] < 0xf0)
        DebugWinPrintf(nbImmediateAdapter, postReceiveNcb[1]);
    else
        DebugWinPrintf(nbImmediateFormatHigh, postReceiveNcb[1],
                       (char far *)NB_RETCODE[postReceiveNcb[1] - 0xa0]);

    return postReceiveNcb[1];
}

void far NbHangUp(unsigned char session)
{
    unsigned char ncb[64];
    memset(ncb, 0, 64);
    ncb[0] = 0x12;
    ncb[2] = session;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS: HangUp.\n");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf(nbFinalFormatLow, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf(nbFinalAdapter, ncb[0x31]);
    else
        DebugWinPrintf(nbFinalFormatHigh, ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
}

int NbCheck(void)
{
    unsigned char ncb[64];
    memset(ncb, 0, 64);
    ncb[0] = 0x7f;
    NetBios((unsigned char far *)ncb);
    if (ncb[0x31] != 3) {
        DebugWinPrintf("NetBIOS not loaded (No response from Int5C).\n");
        return 0;
    }
    return 1;
}

