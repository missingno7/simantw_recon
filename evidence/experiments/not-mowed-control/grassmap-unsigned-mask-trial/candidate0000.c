extern int far GrassMap[];

int NotMowed(int position, unsigned char bit)
{
    unsigned int mask = 1U << bit;
    if (GrassMap[position] & mask) {
        GrassMap[position] -= mask;
        return 1;
    }
    return 0;
}
