extern int far GrassMap[];

int NotMowed(int position, unsigned char bit)
{
    register int pos = position;
    register int mask = 1 << bit;
    if (GrassMap[pos] & mask) {
        GrassMap[pos] -= mask;
        return 1;
    }
    return 0;
}
