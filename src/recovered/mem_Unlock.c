/* Byte-matched reconstruction of the KERNEL GlobalUnlock wrapper. */
extern int far pascal GlobalUnlock(unsigned int handle);

int mem_Unlock(unsigned int handle)
{
    return GlobalUnlock(handle);
}
