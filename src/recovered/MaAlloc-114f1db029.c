/* Allocate zeroed storage for one object. */
extern void far * calloc(unsigned, unsigned);
void far * MaAlloc(unsigned bytes)
{
    return calloc(1, bytes);
}
