static int near openDBInitialized = 0;
extern unsigned char far match_position[];

int GetFreeHandle(void)
{
    unsigned int offset;
    int count;

    if (openDBInitialized != 0)
        goto scan_slots;

    openDBInitialized = 1;
    for (offset = 0x7408; offset < 0x75f8; offset += 0x7c)
        match_position[offset] = 0;

scan_slots:
    count = 0;
    offset = 0x7408;
    while (match_position[offset] != 0) {
        ++count;
        offset += 0x7c;
        if (offset >= 0x75f8)
            return -1;
    }
    return count;
}
