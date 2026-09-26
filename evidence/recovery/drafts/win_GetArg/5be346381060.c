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
    int packedCopy;

    packedCopy = packed;
    if ((signed char)(packedCopy >> 8) > win_numOfWindows || packedCopy >= 0x2800)
        return ((int far *)win_handles[packedCopy >> 8])[index + 8];
    return 0x8000;
}
