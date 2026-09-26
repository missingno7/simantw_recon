/* Copy a counted byte range by advancing the by-value 16:16 pointer words. */
void far MaMemCpy(unsigned char far *destination, const unsigned char far *source, unsigned long length)
{
    while (length != 0UL) {
        *destination = *source;
        *(unsigned long near *)&destination += 1UL;
        *(unsigned long near *)&source += 1UL;
        --length;
    }
}
