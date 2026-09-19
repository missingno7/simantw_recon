/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
int IsThisEgg(unsigned char value)
{
    int normalized;
    normalized = value;
    normalized &= 0x7f;
    if (normalized >= 1 && normalized <= 7) return 1;
    return 0;
}
