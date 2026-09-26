/* Pad a 16-byte name with spaces, copy the source prefix, and terminate. */
void CopyName(char far *destination, const char far *source)
{
    unsigned i;
    unsigned length = 0;
    for (i = 0; i < 16; ++i)
        destination[i] = ' ';
    while (source[length] != 0)
        ++length;
    if (length > 16)
        length = 16;
    for (i = 0; i < length; ++i)
        destination[i] = source[i];
    destination[15] = 0;
}
