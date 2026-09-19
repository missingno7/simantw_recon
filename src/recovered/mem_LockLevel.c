/* Candidate reconstruction of the GlobalFlags lock-level query. */
extern unsigned int far pascal GlobalFlags(unsigned int handle);

int mem_LockLevel(int handle)
{
    unsigned int flags;
    if (handle) {
        flags = GlobalFlags(handle);
        if (flags & 0x100) return flags & 0xff;
        return 1;
    }
    return 0;
}
