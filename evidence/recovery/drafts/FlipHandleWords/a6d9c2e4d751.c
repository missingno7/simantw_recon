extern unsigned long mem_Size(unsigned handle);

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

void far FlipHandleWords(unsigned int handle)
{
    int count, remaining;
    unsigned short far *words;
    unsigned short value;

    count = (int)(mem_Size(handle) >> 1);
    words = (unsigned short far *)mem_Lock(handle);
    if (count > 0) {
        remaining = count;
        do {
            value = *words;
            *words++ = (unsigned short)((value << 8) | (value >> 8));
        } while (--remaining);
    }
    mem_Unlock(handle);
}



