/* Byte-matched reconstruction of the KERNEL GlobalLock wrapper. */
extern void far * far pascal GlobalLock(unsigned int handle);

void far * mem_Lock(unsigned int handle)
{
    return GlobalLock(handle);
}
