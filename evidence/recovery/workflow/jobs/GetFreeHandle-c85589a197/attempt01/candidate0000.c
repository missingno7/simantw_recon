/*
 * Hypothesis: GetFreeHandle lazily clears the first byte of each 0x7c-byte
 * open-database slot, then counts consecutive occupied slots from the same
 * PACK buffer.  The private flag prevents repeating initialization; the
 * count is returned as the first free handle, or -1 when initialization has
 * already been completed by another owner.
 */
static int openDBInitialized;
extern unsigned char far openDBData[];

int GetFreeHandle(void)
{
    unsigned char far *slot;
    int count;

    if (openDBInitialized == 0) {
        openDBInitialized = 1;
        for (slot = openDBData;
             slot < openDBData + 0x1f0;
             slot += 0x7c)
            *slot = 0;
    }

    count = 0;
    for (slot = openDBData;
         *slot != 0 && slot < openDBData + 0x1f0;
         slot += 0x7c)
        ++count;
    return count;
}
