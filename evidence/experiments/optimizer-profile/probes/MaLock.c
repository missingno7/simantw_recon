/* Lock a nonzero global memory handle, returning null for zero. */
extern void far * far pascal GlobalLock(unsigned);
void far * MaLock(unsigned handle)
{
    if (handle)
        return GlobalLock(handle);
    return 0L;
}
