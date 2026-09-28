/*
 * Packed window arguments use the signed high byte to select a far object
 * table.  Values below the current private limit, or outside the packed
 * range, report the historical invalid-argument marker.  Valid entries are
 * word-indexed from offset 0x10 in the selected object.
 */
extern int __based(__segname("PACK")) win_numOfWindows;
extern void far * near win_handles[];

int win_GetArg(int packed, int index)
{
    if (win_numOfWindows > (signed char)(packed >> 8) || packed >= 0x2800)
        return 0x8000;
    return ((int far *)win_handles[(signed char)(packed >> 8)])[8 + index];
}
