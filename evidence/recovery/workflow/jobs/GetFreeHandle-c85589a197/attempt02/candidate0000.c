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
    int offset;
    int count;

    if (openDBInitialized == 0) {
        openDBInitialized = 1;
        for (offset = 0; offset < 0x1f0; offset += 0x7c)
            openDBData[offset] = 0;
    }

    count = 0;
    for (offset = 0;
         openDBData[offset] != 0 && offset < 0x1f0;
         offset += 0x7c)
        ++count;
    if (offset < 0x1f0)
        return count;
    return -1;
}
