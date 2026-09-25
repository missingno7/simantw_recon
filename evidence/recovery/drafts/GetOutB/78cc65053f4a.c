/*
 * GetOutB: try to dig the B-colony ant at map row x (idx = x<<6, so the
 * function always operates on column 0 of that row) out of a hole.  If
 * MapB[idx] is tile 0x18 (a sealed hole), the list record's type byte
 * BlistT[Tindex] is read then cleared, a fresh HoleMapB[x] entry is
 * created via MakeNewHoleB(x) if none exists yet, and ExitHole is tried
 * with the hole map entry, x, a SRand8()-perturbed copy of the type
 * byte's attribute bits, the mode byte and the stamina byte; success
 * clears the sealed tile and reports 1, failure restores the type byte,
 * zeroes the mode byte, and reports 0.
 *
 * Otherwise (not a sealed hole) a per-row Dx8[idx+0x3a4] counter (no
 * confirmed MAPSYM name) is decremented if nonzero, then a SRand2()
 * roll picks a side to try digging toward: SRand2()==0 tries the tile
 * one row further (x+1, x<0x3f guard) via Dx8[idx+0x4929]; otherwise
 * tries one row back (x-1, x>0 guard) via Dx8[idx+0x48a9] -- either
 * side only actually digs (DigTileThemB(x +/- 1, 1)) when IsItDirt says
 * so.  Either way the ant then makes a plain TryMoveDirB(x, 1,
 * SRand8()) attempt (fixed target row 1, result discarded) and the
 * function always returns 0 on this path.
 *
 * Requires the og profile (/Oeglw); only the row index idx survives as
 * a stack local (enter 2, 0).
 */
extern int far Tindex;
extern unsigned char far Dx8[];
extern unsigned char near MapB[];
extern unsigned char near HoleMapB[];

extern void far MakeNewHoleB(int x);
extern int far ExitHole(int hole, int x, int val, int mode, int stam);
extern int far SRand8(void);
extern int far SRand2(void);
extern int far IsItDirt(int tile);
extern void far DigTileThemB(int x, int count);
extern int far TryMoveDirB(int x, int y, int dir);

int far GetOutB(int x)
{
    int idx;
    unsigned char raw;

    idx = x << 6;
    if (MapB[idx] == 0x18) {
        raw = Dx8[Tindex + 0x3d18];
        Dx8[Tindex + 0x3d18] = 0;
        if (HoleMapB[x] == 0)
            MakeNewHoleB(x);
        if (ExitHole(HoleMapB[x], x, SRand8() + (raw & 0xf8),
                      Dx8[Tindex + 0x3b22], Dx8[Tindex + 0x3f0e]) != 0) {
            MapB[idx] = 0;
            return 1;
        }
        Dx8[Tindex + 0x3d18] = raw;
        Dx8[Tindex + 0x3b22] = 0;
        return 0;
    }

    if (Dx8[idx + 0x3a4] != 0)
        Dx8[idx + 0x3a4]--;

    if (SRand2() == 0) {
        if (x < 0x3f && IsItDirt(Dx8[idx + 0x4929]) != 0)
            DigTileThemB(x + 1, 1);
    } else {
        if (x > 0 && IsItDirt(Dx8[idx + 0x48a9]) != 0)
            DigTileThemB(x - 1, 1);
    }

    TryMoveDirB(x, 1, SRand8());
    return 0;
}
