/* Unlock a nonzero global memory handle. */
extern unsigned far pascal GlobalUnlock(unsigned);
void MaUnlock(unsigned handle)
{
    if (handle)
        GlobalUnlock(handle);
}
