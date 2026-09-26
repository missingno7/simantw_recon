/* Keep the forward and reverse loops in separate blocks with independent counters. */
void far MaMemMove(unsigned char far *destination, unsigned char far *source, unsigned long length)
{
    unsigned char far *d;
    unsigned char far *s;
    unsigned long count;
    if (destination >= source) {
        *(unsigned long near *)&destination += length;
        *(unsigned long near *)&source += length;
        *(unsigned long near *)&destination -= 1UL;
        *(unsigned long near *)&source -= 1UL;
        while (length != 0UL) {
            *destination = *source;
            *(unsigned long near *)&destination -= 1UL;
            *(unsigned long near *)&source -= 1UL;
            --length;
        }
        return;
    }
    d = destination;
    s = source;
    count = length;
    while (count != 0UL) {
        *d = *s;
        *(unsigned long near *)&d += 1UL;
        *(unsigned long near *)&s += 1UL;
        --count;
    }
}
