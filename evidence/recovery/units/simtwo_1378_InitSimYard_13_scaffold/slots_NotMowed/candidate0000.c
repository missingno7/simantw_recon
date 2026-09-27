extern int far GrassMap[];

/* Retain the word-sized bit formal but narrow only the shift count. */
int NotMowed(int position, int bit)
{
    int mask = 1 << (unsigned char)bit;

    if (GrassMap[position] & mask) {
        GrassMap[position] -= mask;
        return 1;
    }
    return 0;
}
