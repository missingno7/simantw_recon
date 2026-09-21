extern unsigned int far pascal GlobalReAlloc(unsigned int handle,
                                             unsigned long bytes,
                                             int flags);
extern unsigned long far pascal GlobalCompact(unsigned long minimum);

unsigned int far mem_Realloc(unsigned int handle, unsigned long bytes,
                             int kind)
{
    int flags;
    unsigned int result;

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
    result = GlobalReAlloc(handle, bytes, flags);
    if (result == 0) {
        GlobalCompact(0xffffffffL);
        result = GlobalReAlloc(handle, bytes, flags);
    }
    return result;
}
