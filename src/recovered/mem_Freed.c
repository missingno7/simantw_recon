/* Candidate reconstruction of the GlobalFlags discard-state query. */
extern unsigned int far pascal GlobalFlags(unsigned int handle);

int mem_Freed(unsigned int handle)
{
    unsigned int flags;
    flags = GlobalFlags(handle);
    if (flags & 0x100) return (flags & 0x4000) != 0;
    return 0;
}
