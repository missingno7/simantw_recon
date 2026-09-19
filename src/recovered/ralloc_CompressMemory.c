/* Byte-matched reconstruction of the allocator GlobalCompact wrapper. */
extern unsigned long far pascal GlobalCompact(unsigned long minimum);

unsigned long ralloc_CompressMemory(void)
{
    return GlobalCompact(0xffffffffL);
}
