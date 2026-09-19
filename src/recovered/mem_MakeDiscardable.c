/* Byte-matched reconstruction of the KERNEL GlobalReAlloc wrapper. */
extern unsigned int far pascal GlobalReAlloc(unsigned int handle,
                                             unsigned long bytes,
                                             unsigned int flags);

unsigned int mem_MakeDiscardable(unsigned int handle)
{
    return GlobalReAlloc(handle, 0L, 0x180);
}
