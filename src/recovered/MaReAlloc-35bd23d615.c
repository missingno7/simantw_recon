/* Reallocate a far block through the runtime allocator. */
extern void far * realloc(void far *, unsigned);
void far * MaReAlloc(void far *memory, unsigned bytes)
{
    return realloc(memory, bytes);
}
