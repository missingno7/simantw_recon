/* Delegate the resize to the handle-preserving wrapper. */
extern void far * MaReAllocHandle(unsigned, unsigned long);
void far * MaReAlloc(unsigned handle, unsigned long bytes)
{
    return MaReAllocHandle(handle, bytes);
}
