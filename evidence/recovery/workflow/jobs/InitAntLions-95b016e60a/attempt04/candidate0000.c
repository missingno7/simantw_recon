/*
 * InitAntLions (SIMTWO_MODULE, unit simtwo:3EF8; same LionList arrays,
 * Dx8/Dy8 and lionRing objects as _AddAntLion/_SetAntLion in this unit -- see
 * src/recovered/wf_tu_simtwo_3EF8_AddAntLion_2_scaffold-16d1d1e00e.c).
 *
 * Exact MAPSYM bindings confirm _AntsEatenByLions, _InitialLions,
 * _LionListX/Y/M/S/T and the adjacent _Dx8/_Dy8 8-byte tables; the near
 * byte read at DGROUP+0x25e8 (indexed 0..7, added to 0x30 as a SetMap
 * paint value) is the same ring-sprite table used by AddAntLion
 * (lionRing[8] = {1,2,4,7,6,5,3,0}), and the far word first written via an
 * explicit far pointer built from a literal segment8 offset, later read as
 * an index into the LionList* arrays and incremented at the end guarded by
 * "< 9", is LionIndex (matching AddAntLion/SetAntLion's own LionIndex use).
 *
 * InitAntLions(count): resets LionIndex and AntsEatenByLions, clamps count
 * to at most 10, and (if positive) places that many ant lions: for each,
 * retry up to 200 times picking a jittered random spot (two SRand1 calls
 * summed per axis) until IsClear3x3 accepts it outright, or IsClearTile
 * accepts the single tile and at least 100 tries have already been spent
 * (a loosening fallback). Once a spot is accepted: stamp the center tile
 * (SetMap plane 1, value 0x38), ring the 8 neighbours from Dx8/Dy8 with
 * SetMap using lionRing[i]+0x30 wherever IsClearTile allows it, record the
 * position into LionListX/Y and zero LionListM/S/T at the current
 * LionIndex slot, and bump LionIndex while it stays under 9. Finally
 * InitialLions is set to the clamped count.
 */

extern char far Dx8[];
extern char far Dy8[];
extern int far LionIndex;
extern int far AntsEatenByLions;
extern int far InitialLions;
extern unsigned char far LionListX[];
extern unsigned char far LionListY[];
extern unsigned char far LionListM[];
extern unsigned char far LionListS[];
extern unsigned char far LionListT[];
extern int far SRand1(int range);
extern int far IsClear3x3(int plane, int x, int y);
extern int far IsClearTile(int plane, int x, int y);
extern void far SetMap(int plane, int x, int y, int value);

static unsigned char near lionRing[8] = {1, 2, 4, 7, 6, 5, 3, 0};

void far InitAntLions(int count)
{
    int far *pli;
    int remaining;
    int tries;
    int pad1;
    int pad2;
    int x;
    int y;
    int lx;
    int ly;
    int i;

    pli = &LionIndex;
    *pli = 0;
    AntsEatenByLions = 0;

    if (count > 10)
        count = 10;
    if (count > 0) {
        remaining = count;
        do {
            tries = 0;
            for (;;) {
                x = SRand1(0x40) + SRand1(0x41);
                y = SRand1(0x20) + SRand1(0x21);
                if (IsClear3x3(1, x, y) == 1)
                    goto place;
                if (IsClearTile(1, x, y) == 1) {
                    if (tries >= 100)
                        goto place;
                }
                tries++;
                if (tries >= 200)
                    goto skip;
            }
        place:
            SetMap(1, x, y, 0x38);
            for (i = 0; i < 8; i++) {
                ly = y + Dy8[i];
                lx = x + Dx8[i];
                if (IsClearTile(1, lx, ly) == 1)
                    SetMap(1, lx, ly, lionRing[i] + 0x30);
            }
            LionListX[*pli] = x;
            LionListY[*pli] = y;
            LionListM[*pli] = 0;
            LionListS[*pli] = 0;
            LionListT[*pli] = 0;
            if (*pli < 9)
                *pli = *pli + 1;
        skip:
            remaining--;
        } while (remaining != 0);
    }

    InitialLions = count;
}
