/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
int IsYellowAnt(int value)
{
    if (value == 0xff || value == 0xfe) return 1;
    return 0;
}
