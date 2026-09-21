extern unsigned long far mem_Size(unsigned int handle);
extern void far *far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

void far FlipHandleWords(unsigned int handle)
{
    unsigned int count;
    unsigned short near *words;
    unsigned short value;

    count = (unsigned int)(mem_Size(handle) >> 1);
    words = (unsigned short far *)mem_Lock(handle);
    if (count > 0) {
        while (count--) {
            value = *words;
            *words++ = (unsigned short)((value << 8) | (value >> 8));
        }
        mem_Unlock(handle);
    }
}
