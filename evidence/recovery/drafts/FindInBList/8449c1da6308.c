/*
 * Hypothesis: ListIndexB holds the exclusive upper bound of the B list.
 * After switching DS to the far Dx8 list segment, search backward for the
 * first entry whose three byte fields match the three packed-list keys.
 * Restore the caller's DGROUP before returning the matching index or -1.
 */
extern int far ListIndexB;
extern unsigned char far Dx8[];

int FindInBList(int firstKey, int secondKey, int thirdKey)
{
    int index;

    index = ListIndexB;
    while (index > 0) {
        --index;
        if (Dx8[index + 0x3736] == firstKey &&
            Dx8[index + 0x392c] == secondKey &&
            Dx8[index + 0x3d18] == thirdKey)
            return index;
    }
    return -1;
}
