/*
 * Packed window arguments use the signed high byte to select a far object
 * table.  Values below the current private limit, or outside the packed
 * range, report the historical invalid-argument marker.  Valid entries are
 * word-indexed from offset 0x10 in the selected object.
 */
extern int far win_numOfWindows;
extern void far * near win_handles[];

int win_GetArg(int packed, int index)
{
    int group;

    group = (signed char)(packed >> 8);
    if (group > win_numOfWindows)
        goto valid;
    if (packed >= 0x2800)
        goto valid;
    return 0x8000;
valid:
    return ((int far *)win_handles[group])[index + 8];
}
