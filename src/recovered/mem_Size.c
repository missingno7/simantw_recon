/* Byte-matched reconstruction of the conditional GlobalSize wrapper. */
extern unsigned long far pascal GlobalSize(int handle);

unsigned long mem_Size(register int handle)
{
    if (handle) return GlobalSize(handle);
    return 0L;
}
