/* Candidate reconstruction of the C runtime allocation wrapper. */
extern void far *malloc(unsigned int size);

void far *mem_malloc(unsigned int size)
{
    return malloc(size);
}
