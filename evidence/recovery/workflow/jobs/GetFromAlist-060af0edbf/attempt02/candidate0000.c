/*
 * Hypothesis: the A-list index word is stored in PACK at 0x80f0.  A positive
 * index names the next A-list record; after stepping back one record, the
 * high bit of its type byte at 0x2f62 is the requested list class.  A matching
 * nonzero index is removed from the A-list and reported as success; all other
 * paths return zero.
 */
extern int far ListIndexA;
extern unsigned char far Dx8[];
extern int near RemoveFromAList(int index);

int GetFromAlist(int type)
{
    int index;
    int listType;

    index = ListIndexA;
    if (index <= 0)
        return 0;

    --index;
    listType = Dx8[index + 0x2f62];
    if (listType == 0)
        return 0;
    if ((listType >> 7) != type)
        return 0;
    if (index == 0)
        return 0;

    RemoveFromAList(index);
    return 1;
}
