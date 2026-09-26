/* Copy a counted byte range while carrying through huge-pointer arithmetic. */
void MaMemCpy(unsigned char huge *destination, const unsigned char huge *source, unsigned long length)
{
    while (length != 0) {
        *destination++ = *source++;
        --length;
    }
}
