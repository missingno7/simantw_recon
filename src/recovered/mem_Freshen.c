/* Byte-matched reconstruction of the KERNEL GlobalLRUNewest wrapper. */
extern unsigned int far pascal GlobalLRUNewest(unsigned int handle);

unsigned int mem_Freshen(unsigned int handle)
{
    return GlobalLRUNewest(handle);
}
