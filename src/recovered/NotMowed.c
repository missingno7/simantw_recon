extern int far match_position[];

int NotMowed(int position, unsigned char bit)
{
    int mask = 1 << bit;

    if (match_position[position] & mask) {
        match_position[position] -= mask;
        return 1;
    }
    return 0;
}
