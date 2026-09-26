/* Allocate movable zero-initialized global memory. */
extern void far * far pascal GlobalAlloc(unsigned, unsigned long);
void far * MaAllocHandle(unsigned long bytes)
{
    return GlobalAlloc(0x42, bytes);
}
