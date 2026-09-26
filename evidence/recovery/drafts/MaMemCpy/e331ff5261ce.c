/* Copy a counted number of bytes while preserving the parameter values. */
void MaMemCpy(unsigned char far * volatile destination, const unsigned char far * volatile source, volatile unsigned long length)
{
    while (length != 0) {
        *destination = *source;
        destination = destination + 1;
        source = source + 1;
        length = length - 1L;
    }
}
