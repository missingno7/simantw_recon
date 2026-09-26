/* First record construction pass from the gateway allocation path. */
extern unsigned int far GlobalAlloc(unsigned int flags, unsigned long bytes);
extern void far *far GlobalLock(unsigned int handle);
extern unsigned int far GlobalUnlock(unsigned int handle);
extern unsigned int far GlobalFree(unsigned int handle);
extern void far MaMemCpy(void far *destination, void far *source,
                         unsigned long bytes);

struct GatewayRecord {
    int request;
    int source;
    unsigned char input[0x20];
    int inputKind;
    unsigned long inputValue;
    int resultKind;
    int resultCode;
    unsigned long extraBytes;
};

unsigned long far GtAppToGateway(int request, int source,
                                 void far *input, int inputKind,
                                 unsigned long inputValue,
                                 int resultKind, int resultCode,
                                 unsigned long extraBytes,
                                 void far *buffer)
{
    unsigned int handle;
    struct GatewayRecord far *record;

    handle = GlobalAlloc(0x2042, extraBytes + 0x3aUL);
    if (handle == 0)
        return 0xffffffffUL;

    record = (struct GatewayRecord far *)GlobalLock(handle);
    if (record == 0) {
        GlobalFree(handle);
        return 0xffffffffUL;
    }

    record->request = request;
    record->source = source;
    if (input != 0)
        MaMemCpy(record->input, input, sizeof(record->input));
    record->inputKind = inputKind;
    record->inputValue = inputValue;
    record->resultKind = resultKind;
    record->resultCode = resultCode;
    record->extraBytes = extraBytes;
    if (extraBytes != 0 && buffer != 0)
        MaMemCpy((char far *)record + 0x34, buffer, extraBytes);

    GlobalUnlock(handle);
    GlobalFree(handle);
    return 0;
}
