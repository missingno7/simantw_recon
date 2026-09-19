/* Byte-matched reconstruction of the KERNEL GlobalFree wrapper. */
extern unsigned int far pascal GlobalFree(unsigned int handle);

unsigned int mem_Free(unsigned int handle)
{
    return GlobalFree(handle);
}
