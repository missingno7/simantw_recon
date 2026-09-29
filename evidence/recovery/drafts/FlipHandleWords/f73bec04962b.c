extern unsigned long far mem_Size(unsigned int handle);
extern void far *far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

void far FlipHandleWords(unsigned int handle)
{
    int count;
    unsigned short __based(__segname("DS")) *words;
    unsigned short value;

    count = (int)(mem_Size(handle) >> 1);
    words = (unsigned short __based(__segname("DS")) *)mem_Lock(handle);
    if (count > 0) {
        while (count--) {
            value = *words;
            *words++ = (unsigned short)((value << 8) | (value >> 8));
        }
        mem_Unlock(handle);
    }
}
