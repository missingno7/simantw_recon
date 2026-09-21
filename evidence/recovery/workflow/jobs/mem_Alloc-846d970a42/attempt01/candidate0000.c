extern unsigned int far pascal GlobalAlloc(unsigned int flags,
                                           unsigned long bytes);
extern unsigned long far pascal GlobalCompact(unsigned long minimum);

unsigned int far mem_Alloc(unsigned long bytes, int unused, int kind)
{
    int flags;
    unsigned int handle;

    switch (kind) {
    case 0:
    case 1:
    case 2:
        flags = 0x42;
        break;
    case 3:
        flags = 0x142;
        break;
    }
    handle = GlobalAlloc(flags, bytes);
    if (handle == 0) {
        GlobalCompact(0xffffffffL);
        handle = GlobalAlloc(flags, bytes);
    }
    return handle;
}
