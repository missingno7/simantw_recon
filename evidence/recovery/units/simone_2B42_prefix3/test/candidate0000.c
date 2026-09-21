/* Candidate translation unit simone_2B42_prefix3: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _FindInAList, _FindInBList, _FindInRList */

extern unsigned int far AListState[];
extern unsigned char far Dx8[];
extern int far ListIndexB;
extern int far ListIndexR;

int FindInAList(int firstKey, int secondKey)
{
    int index;

    index = AListState[0x4078];
    while (index > 0) {
        --index;
        if (Dx8[index + 0x23a4] == firstKey &&
            Dx8[index + 0x278e] == secondKey &&
            Dx8[index + 0x2f62] != 0)
            return index;
    }
    return -1;
}

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

