/*
 * {s}: the saved list byte is retained across the ExitHole call; R-colony twin of GetOutB, byte-for-byte identical structure
 * (same 314-byte extent, same call sequence MakeNewHoleR/SRand8/
 * ExitHole/SRand2/IsItDirt x2/DigTileThemR/SRand8/TryMoveDirR) with the
 * R-side offsets substituted: MapR[idx] (idx = x<<6) sealed-hole tile
 * 0x18 check; RlistT 0x46e6, RlistS 0x48dc, RlistM 0x44f0 (same Dx8[]
 * object as the B twin); HoleMapR[x]; the unnamed per-row Dx8[idx+CONST]
 * counter is at 0x13a4 here (0x3a4 for B); the two dirt-check offsets
 * are 0x58a9 (x-1 side) and 0x5929 (x+1 side).
 *
 * See GetOutB.c for the full semantic account: sealed-hole path reads
 * and clears RlistT[Tindex], creates a hole entry via MakeNewHoleR(x)
 * when HoleMapR[x]==0, tries ExitHole(HoleMapR[x], x,
 * SRand8()+(raw&0xf8), RlistM[Tindex], RlistS[Tindex]) -- success
 * clears the tile and returns 1, failure restores RlistT[Tindex],
 * zeroes RlistM[Tindex] and returns 0; otherwise the per-row counter is
 * decremented if nonzero, a SRand2() roll and IsItDirt gate a
 * DigTileThemR(x +/- 1, 1) call, and a TryMoveDirR(x, 1, SRand8())
 * attempt always ends the turn with a 0 return.
 *
 * Requires the og profile (/Oeglw); only idx survives as a stack local
 * (enter 2, 0).
 */
extern int __based(__segname("PACK")) Tindex;
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistS[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistM[];
extern unsigned char near MapR[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) HoleMapR[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) ExitMapR[];

extern void far MakeNewHoleR(int x);
extern int far ExitHole(int hole, int x, int val, int mode, int stam);
extern int far SRand8(void);
extern int far SRand2(void);
extern int far IsItDirt(int tile);
extern void far DigTileThemR(int x, int count);
extern int far TryMoveDirR(int x, int y, int dir);

int far GetOutR(int x)
{
    int idx;
    int raw;

    idx = x << 6;
    if (MapR[idx] == 0x18) {
        raw = RlistT[Tindex];
        RlistT[Tindex] = 0;
        if (HoleMapR[x] == 0)
            MakeNewHoleR(x);
        if (ExitHole(HoleMapR[x], x, SRand8() + (raw & 0xf8),
                      RlistM[Tindex], RlistS[Tindex]) != 0) {
            MapR[idx] = 0;
            return 1;
        }
        RlistT[Tindex] = raw;
        RlistM[Tindex] = 0;
        return 0;
    }

    if (ExitMapR[idx] != 0)
        ExitMapR[idx]--;

    if (SRand2() != 0) {
        if (x > 0 && IsItDirt(MapR[idx - 0x3f]) != 0)
            DigTileThemR(x - 1, 1);
    } else {
        if (x < 0x3f && IsItDirt(MapR[idx + 0x41]) != 0)
            DigTileThemR(x + 1, 1);
    }

    TryMoveDirR(x, 1, SRand8());
    return 0;
}
