/* Release a far allocation. */
extern void free(void far *);
void MaFree(void far *memory)
{
    free(memory);
}
