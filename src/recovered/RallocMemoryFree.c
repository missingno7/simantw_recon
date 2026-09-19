/* Byte-matched reconstruction of the KERNEL GetFreeSpace wrapper. */
extern unsigned long far pascal GetFreeSpace(unsigned int flags);

unsigned long RallocMemoryFree(void)
{
    return GetFreeSpace(0);
}
