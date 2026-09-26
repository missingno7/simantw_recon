/* First pass over card resource loading and handle locking. */
extern unsigned int far db_LoadObject(int objectNumber, int kind, int lock);
extern void far *far mem_Lock(unsigned int handle);
extern void far mem_Unlock(void far *block);
extern void far db_ReleaseHandle(unsigned int handle);

void far DisplayCard(int cardNumber)
{
    int cardKind;
    int reserved;
    unsigned int cardHandle;
    unsigned int textHandle;
    void far *cardData;
    void far *textData;

    cardKind = 4;
    reserved = 0;
    cardHandle = db_LoadObject(cardNumber, 0x11, 1);
    if (cardHandle == 0)
        return;

    cardData = mem_Lock(cardHandle);
    if (cardData == 0) {
        db_ReleaseHandle(cardHandle);
        return;
    }

    textHandle = db_LoadObject(cardNumber, 0x13, 1);
    if (textHandle != 0) {
        textData = mem_Lock(textHandle);
        if (textData != 0)
            mem_Unlock(textData);
        db_ReleaseHandle(textHandle);
    }

    mem_Unlock(cardData);
    db_ReleaseHandle(cardHandle);
}
