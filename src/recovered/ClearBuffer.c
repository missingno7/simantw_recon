/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
void ClearBuffer(unsigned char far *buffer, unsigned int count)
{
    while (count--) *buffer++ = 0;
}
