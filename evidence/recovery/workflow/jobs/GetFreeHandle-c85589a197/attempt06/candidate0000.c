/*
 * Hypothesis: GetFreeHandle lazily clears the first byte of each 0x7c-byte
 * open-database slot, then counts consecutive occupied slots from the same
 * PACK buffer.  The private flag prevents repeating initialization; the
 * count is returned as the first free handle, or -1 when initialization has
 * already been completed by another owner.
 */
static int openDBInitialized = 0;
extern unsigned char far match_position[];
typedef unsigned char __based(__segname("PACK")) *PackBytePtr;

int GetFreeHandle(void)
{
    PackBytePtr slot;
    int count;

    if (openDBInitialized != 0)
        goto scan_slots;

    openDBInitialized = 1;
    for (slot = (PackBytePtr)0x7408;
         slot < (PackBytePtr)0x75f8;
         slot += 0x7c)
        *slot = 0;

scan_slots:
    count = 0;
    for (slot = (PackBytePtr)0x7408;
         *slot != 0 && slot < (PackBytePtr)0x75f8;
         slot += 0x7c) {
        ++count;
    }
    if (slot < (PackBytePtr)0x75f8)
        return count;
    return -1;
}
