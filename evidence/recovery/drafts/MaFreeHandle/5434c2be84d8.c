/* Release a global memory handle. */
extern unsigned far pascal GlobalFree(unsigned);
unsigned MaFreeHandle(unsigned handle)
{
    return GlobalFree(handle);
}
