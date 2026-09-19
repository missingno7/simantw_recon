/* Byte-matched reconstruction of the KERNEL GlobalCompact wrapper. */
extern unsigned long far pascal GlobalCompact(unsigned long minimum);

unsigned long mem_Flush(void)
{
    return GlobalCompact(0xffffffffL);
}
