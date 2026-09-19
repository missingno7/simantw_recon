/* Candidate reconstruction of the C runtime release wrapper. */
extern void free(void far *block);

void mem_free(void far *block)
{
    free(block);
}
