/* Exchange the low and high words of a far long in place. */
void XFlipLong(unsigned far *words)
{
    unsigned first = words[0];
    words[0] = words[1];
    words[1] = first;
}
