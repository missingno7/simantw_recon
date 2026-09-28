extern unsigned long mem_Size(unsigned handle);
extern void far *far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

void far FlipHandleWords(unsigned int handle)
{
    union {
        void far *pointer;
        struct {
            unsigned int offset;
            __segment selector;
        } parts;
    } locked;
    __segment selector;
    unsigned int count;
    unsigned short __based(selector) *words;
    unsigned short value;

    count = (unsigned int)(mem_Size(handle) >> 1);
    locked.pointer = mem_Lock(handle);
    selector = locked.parts.selector;
    words = (unsigned short __based(selector) *)locked.parts.offset;
    if (count > 0) {
        while (count--) {
            value = *words;
            *words++ = (unsigned short)((value << 8) | (value >> 8));
        }
        mem_Unlock(handle);
    }
}
