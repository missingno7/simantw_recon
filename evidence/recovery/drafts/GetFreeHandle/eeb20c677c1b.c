static int openDBInitialized = 0;
extern unsigned char far match_position[];

int GetFreeHandle(void)
{
    register unsigned char far *slot;
    int count;

    if (openDBInitialized != 0)
        goto scan;
    openDBInitialized = 1;
    slot = match_position + 0x7408;
    do {
        *slot = 0;
        slot += 0x7c;
    } while (slot < match_position + 0x75f8);

scan:
    count = 0;
    slot = match_position + 0x7408;
    while (*slot != 0) {
        ++count;
        slot += 0x7c;
        if (slot >= match_position + 0x75f8)
            goto no_slots;
    }
    return count;

no_slots:
    return -1;
}
