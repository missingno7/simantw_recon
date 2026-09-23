extern int far GrassMap[];

int NotMowed(int position, unsigned char bit)
{
    int index = position;
    int mask = 1 << bit;
    if (GrassMap[index] & mask) {
        GrassMap[index] -= mask;
        return 1;
    }
    return 0;
}
