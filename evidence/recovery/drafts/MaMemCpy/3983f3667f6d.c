/* Copy a counted number of bytes between far pointers. */
void MaMemCpy(void far *destination, const void far *source, unsigned long length)
{
    unsigned char far *out = (unsigned char far *)destination;
    const unsigned char far *in = (const unsigned char far *)source;
    while (length != 0) {
        *out++ = *in++;
        --length;
    }
}
