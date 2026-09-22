/*
 * DoReturnFoodAnt: per-tick behavior for an A-list ant (index) that is
 * carrying food back to the nest. If its current cell (AlistX[index],
 * AlistY[index]) is a valid in-range nest-hole tile (MapA cell == 0x50
 * when TERRAINset is clear, in 0x80-0x8f when set -- the inline
 * IsItHole test), the ant enters the nest (GoInNest). Otherwise
 * GetNestDir(x, y, dir, attribute) picks a direction-table index, Dx8/
 * Dy8 give the signed step for that index, and the stepped cell's MapA
 * value is compared against the far Barrier threshold: over the
 * threshold the ant instead turns via TurnTab[(attribute&7)*8 +
 * SRand8()] (preserving the upper attribute flag bits in AlistT and
 * LifeA at its current cell) and returns without moving; at or under
 * the threshold the move commits -- LifeA is marked at the new cell and
 * cleared at the old one, AlistX/AlistY/AlistT are updated, and if
 * AlistS (stamina/food count) is still positive it is decremented and a
 * scent is jammed toward the nest at the new cell: JamScentRT when the
 * ant's team bit (attribute & 0x80) is set, JamScentBT otherwise.
 * AlistX/AlistY/AlistT/AlistS, Dx8/Dy8, TurnTab, Barrier, TERRAINset and
 * MapA/LifeA are the exact MAPSYM names from direct_data_bindings.
 * IsValidA, SRand8, JamScentRT and JamScentBT reuse
 * src/recovered/IsValidA.c, src/recovered/SRand8.c,
 * src/recovered/wf_JamScentRT-49b609e816.c and
 * src/recovered/wf_JamScentBT-86d27c2a8a.c; GoInNest and GetNestDir are
 * unit neighbours (_GoInNest, near_call; GetNestDir, far, segment 7)
 * without an admitted declaration yet.
 */
extern unsigned char far AlistX[];
extern unsigned char far AlistY[];
extern unsigned char far AlistT[];
extern unsigned char far AlistS[];
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char far TurnTab[];
extern unsigned int far Barrier;
extern unsigned int far TERRAINset;
extern unsigned char near MapA[];
extern unsigned char near LifeA[];

extern int far IsValidA(int x, int y);
extern int far GetNestDir(int x, int y, int dir, int attribute);
extern int far SRand8(void);
extern void near GoInNest(int x, int y, int index);
extern void near JamScentRT(int x, int y, int scent);
extern void far JamScentBT(int x, int y, int scent);

void near DoReturnFoodAnt(int index)
{
    int x, y;
    int attribute;
    int found;
    int nx, ny, ndir;
    int newtile;
    int flags;
    int scent;

    x = AlistX[index] & 0xff;
    y = AlistY[index];
    attribute = AlistT[index];

    if (!IsValidA(x, y)) {
        found = 0;
        goto check_hole;
    }
    if (TERRAINset == 0) {
        if (MapA[x * 64 + y] != 0x50) {
            found = 0;
            goto check_hole;
        }
    } else {
        newtile = MapA[x * 64 + y];
        if (newtile < 0x80 || newtile > 0x8f) {
            found = 0;
            goto check_hole;
        }
    }
    found = 1;

check_hole:
    if (found) {
        GoInNest(x, y, index);
        return;
    }

    flags = attribute & 0xf8;
    ndir = GetNestDir(x, y, attribute & 7, attribute);
    nx = x + (signed char)Dx8[ndir];
    ny = y + (signed char)Dy8[ndir];
    newtile = MapA[nx * 64 + ny];

    if (newtile > Barrier) {
        attribute = TurnTab[(attribute & 7) * 8 + SRand8()] | flags;
        AlistT[index] = (unsigned char)attribute;
        LifeA[x * 64 + y] = (unsigned char)attribute;
        return;
    }

    LifeA[nx * 64 + ny] = (unsigned char)attribute;
    AlistT[index] = (unsigned char)attribute;
    LifeA[x * 64 + y] = 0;
    AlistX[index] = (unsigned char)nx;
    AlistY[index] = (unsigned char)ny;

    if (AlistS[index] != 0) {
        AlistS[index]--;
        scent = AlistS[index];
        if (attribute & 0x80)
            JamScentRT(nx, ny, scent);
        else
            JamScentBT(nx, ny, scent);
    }
}
