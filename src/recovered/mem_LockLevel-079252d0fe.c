/* mem_LockLevel: inspect the kernel GlobalFlags lock bit and return the
 * low flag byte when locked; otherwise report the one-level state. */
extern unsigned far pascal GlobalFlags(unsigned handle);

int mem_LockLevel(unsigned handle)
{
    unsigned flags;

    if (handle) {
        flags = GlobalFlags(handle);
        if (flags & 0x100)
            return (unsigned char)flags;
        return 1;
    }
    return 0;
}
