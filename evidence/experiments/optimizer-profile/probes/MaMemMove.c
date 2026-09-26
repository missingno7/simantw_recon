/* Copy each byte explicitly; the backward path begins at the final byte of
   the same far ranges. */
void far MaMemMove(unsigned char far *destination,
                   unsigned char far *source,
                   unsigned long length)
{
    if (destination < source) {
        while (length != 0UL) {
            *destination = *source;
            ++destination;
            ++source;
            --length;
        }
    } else {
        destination += length - 1UL;
        source += length - 1UL;
        while (length != 0UL) {
            *destination = *source;
            --destination;
            --source;
            --length;
        }
    }
}
