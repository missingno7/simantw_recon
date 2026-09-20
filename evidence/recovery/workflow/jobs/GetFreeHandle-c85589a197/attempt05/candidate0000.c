/*
 * Hypothesis: GetFreeHandle lazily clears the first byte of each 0x7c-byte
 * open-database slot, then counts consecutive occupied slots from the same
 * PACK buffer.  The private flag prevents repeating initialization; the
 * count is returned as the first free handle, or -1 when initialization has
 * already been completed by another owner.
 */
static int openDBInitialized = 0;
extern unsigned char far match_position[];

int GetFreeHandle(void)
{
    unsigned char near *slot;
    unsigned char near *end;
    int count;

    end = (unsigned char near *)(match_position + 0x75f8);
    if (openDBInitialized != 0)
        goto scan_slots;

    openDBInitialized = 1;
    slot = (unsigned char near *)(match_position + 0x7408);
    end = slot + 0x1f0;
    for (; slot < end; slot += 0x7c)
        *slot = 0;

scan_slots:
    count = 0;
    slot = (unsigned char near *)(match_position + 0x7408);
    for (; *slot != 0 && slot < end; slot += 0x7c) {
        ++count;
    }
    if (slot < end)
        return count;
    return -1;
}
