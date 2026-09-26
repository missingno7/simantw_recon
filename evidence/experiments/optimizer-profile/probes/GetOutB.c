/*
 * {s}: the saved list byte is retained across the ExitHole call; try to dig the B-colony ant at map row x (idx = x<<6, so the
 * function always operates on column 0 of that row) out of a hole.  If
 * MapB[idx] is tile 0x18 (a sealed hole), the list record's type byte
 * BlistT[Tindex] is read then cleared, a fresh HoleMapB[x] entry is
 * created via MakeNewHoleB(x) if none exists yet, and ExitHole is tried
 * with the hole map entry, x, a SRand8()-perturbed copy of the type
 * byte's attribute bits, the mode byte and the stamina byte; success
 * clears the sealed tile and reports 1, failure restores the type byte,
 * zeroes the mode byte, and reports 0.
 *
 * Otherwise (not a sealed hole) the per-row ExitMapB[idx] value is decremented if nonzero, then a SRand2()
 * roll picks a side to try digging toward: SRand2()==0 tries the tile
 * one row further (x+1, x<0x3f guard) via MapB[idx+0x41]; otherwise
 * tries one row back (x-1, x>0 guard) via MapB[idx-0x3f] -- either
 * side only actually digs (DigTileThemB(x +/- 1, 1)) when IsItDirt says
 * so.  Either way the ant then makes a plain TryMoveDirB(x, 1,
 * SRand8()) attempt (fixed target row 1, result discarded) and the
 * function always returns 0 on this path.
 *
 * Requires the og profile (/Oeglw); only the row index idx survives as
 * a stack local (enter 2, 0).
 */
extern int __based(__segname("PACK")) Tindex;
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistS[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistM[];
extern unsigned char near MapB[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) HoleMapB[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) ExitMapB[];

extern void far MakeNewHoleB(int x);
extern int far ExitHole(int hole, int x, int val, int mode, int stam);
extern int far SRand8(void);
extern int far SRand2(void);
extern int far IsItDirt(int tile);
extern void far DigTileThemB(int x, int count);
extern int far TryMoveDirB(int x, int y, int dir);

int far GetOutB(int x)
{
    volatile int idx;
    int raw;

    idx = x << 6;
    if (MapB[idx] == 0x18) {
        raw = BlistT[Tindex];
        BlistT[Tindex] = 0;
        if (HoleMapB[x] == 0)
            MakeNewHoleB(x);
        if (ExitHole(HoleMapB[x], x, SRand8() + (raw & 0xf8),
                      BlistM[Tindex], BlistS[Tindex]) != 0) {
            MapB[idx] = 0;
            return 1;
        }
        BlistT[Tindex] = raw;
        BlistM[Tindex] = 0;
        return 0;
    }

    if (ExitMapB[idx] != 0)
        ExitMapB[idx]--;

    if (SRand2() != 0) {
        if (x > 0 && IsItDirt(MapB[idx - 0x3f]) != 0)
            DigTileThemB(x - 1, 1);
    } else {
        if (x < 0x3f && IsItDirt(MapB[idx + 0x41]) != 0)
            DigTileThemB(x + 1, 1);
    }

    TryMoveDirB(x, 1, SRand8());
    return 0;
}
