/*
 * Hypothesis: direction codes 0, 2, 3, 0x5e..0x61, 0x66, and 0x68
 * describe the legal house-hole cases.  The middle range is translated
 * into the corresponding hole code by adding 0x22; every other code is
 * rejected with zero.
 */
int CanBeHouseHole(int direction)
{
    if (direction == 0)
        return 0x86;

    if (direction == 2 || direction == 3)
        return 0x8a;

    if (direction < 0x5e)
        return 0;
    if (direction < 0x62)
        return direction + 0x22;

    if (direction == 0x66)
        return 0x85;
    if (direction == 0x68)
        return 0x84;
    return 0;
}
