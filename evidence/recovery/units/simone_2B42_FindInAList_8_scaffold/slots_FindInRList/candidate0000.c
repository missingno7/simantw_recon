/*
 * Hypothesis: ListIndexR is the exclusive upper bound of the R list.
 * Switch DS to Dx8, scan indices backward, and return the first entry whose
 * three byte fields match the requested x, y, and type keys.  Restore DS on
 * both the match and exhausted-list paths.
 */
extern int far ListIndexR;
extern unsigned char far Dx8[];

int FindInRList(int firstKey, int secondKey, int thirdKey)
{
    int index;

    index = ListIndexR;
    while (index > 0) {
        --index;
        if (Dx8[index + 0x4104] == firstKey &&
            Dx8[index + 0x42fa] == secondKey &&
            Dx8[index + 0x46e6] == thirdKey)
            return index;
    }
    return -1;
}
