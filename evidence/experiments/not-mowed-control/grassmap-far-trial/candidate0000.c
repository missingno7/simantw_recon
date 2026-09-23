extern int far GrassMap[];

int NotMowed(int position, unsigned char bit)
{
    int mask = 1 << bit;

    if (GrassMap[position] & mask) {
        GrassMap[position] -= mask;
        return 1;
    }
    return 0;
}
