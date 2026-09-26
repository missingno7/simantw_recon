/* Copy a counted number of bytes between far pointers. */
void MaMemCpy(unsigned char far *destination, const unsigned char far *source, unsigned long length)
{
    while (length != 0) {
        *destination++ = *source++;
        --length;
    }
}
