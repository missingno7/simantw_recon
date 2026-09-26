/* Swap the two 16-bit halves of a far long in place. */
void XFlipLong(unsigned long far *value)
{
    unsigned far *words = (unsigned far *)value;
    unsigned first = words[0];
    words[0] = words[1];
    words[1] = first;
}
