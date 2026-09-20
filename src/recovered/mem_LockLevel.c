extern unsigned far pascal GlobalFlags(unsigned handle);

int mem_LockLevel(unsigned handle)
{
    unsigned flags;

    if (!handle)
        return 0;
    flags = GlobalFlags(handle);
    if (!(flags & 0x100))
        return 1;
    return (unsigned char)flags;
}
