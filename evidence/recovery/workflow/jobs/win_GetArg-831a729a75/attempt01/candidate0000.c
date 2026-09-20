/*
 * Packed window arguments use the signed high byte to select a far object
 * table.  Values below the current private limit, or outside the packed
 * range, report the historical invalid-argument marker.  Valid entries are
 * word-indexed from offset 0x10 in the selected object.
 */
extern int far win_ArgLimit;
extern unsigned char far *far win_ArgTable[];

int win_GetArg(int packed, int index)
{
    int group;

    group = (signed char)(packed >> 8);
    if (win_ArgLimit > group || packed >= 0x2800)
        return 0x8000;
    return *(int far *)((unsigned char far *)win_ArgTable[group]
                        + 0x10 + index * 2);
}
