/* Resize a global handle with the memory manager's fixed allocation flags. */
extern void far * far pascal GlobalReAlloc(unsigned, unsigned long, unsigned);
void far * MaReAllocHandle(unsigned handle, unsigned long bytes)
{
    return GlobalReAlloc(handle, bytes, 0x42);
}
