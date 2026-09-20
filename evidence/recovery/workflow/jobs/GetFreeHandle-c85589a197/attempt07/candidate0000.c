/*
 * Hypothesis: GetFreeHandle lazily clears the first byte of each 0x7c-byte
 * open-database slot, then counts consecutive occupied slots from the same
 * PACK buffer.  The private flag prevents repeating initialization; the
 * count is returned as the first free handle, or -1 when initialization has
 * already been completed by another owner.
 */
static int openDBInitialized = 0;
extern unsigned char far match_position[];
typedef unsigned char __based(match_position) *PackBytePtr;

int GetFreeHandle(void)
{
    unsigned int offset;
    int count;

    if (openDBInitialized != 0)
        goto scan_slots;

    openDBInitialized = 1;
    for (offset = 0x7408; offset < 0x75f8; offset += 0x7c)
        *((PackBytePtr)offset) = 0;

scan_slots:
    count = 0;
    for (offset = 0x7408;
         *((PackBytePtr)offset) != 0 && offset < 0x75f8;
         offset += 0x7c) {
        ++count;
    }
    if (offset < 0x75f8)
        return count;
    return -1;
}
