/*
 * DoDigOutAntA: per-tick behavior for an A-list ant (index) that is
 * digging. attribute's bits split into flags (0xf8), a dig sub-mode
 * digmode ((attribute&0x78)>>3, 0-15) and a direction (attribute&7).
 * TurnTab[(attribute&7)*8 + SRand8()] gives a candidate new direction
 * index; if the ant is on the map edge, Bounce(x,y) overrides it with a
 * bounced direction instead. Dx8/Dy8 step that direction to (nx,ny).
 *
 * digmode outside {5,9}: the ant just changes AlistM (GetNewMode) and
 * resets AlistS, without moving. digmode 5 or 9, when SRand8()==0,
 * additionally finishes at the current cell: AlistT loses 0x18 (a
 * progress counter step) and LifeA at the current cell is refreshed
 * with the new AlistT. Otherwise the ant tries to move: if the stepped
 * cell's MapA value exceeds Barrier, or the stepped cell's LifeA is
 * already occupied, the ant instead turns in place (a fresh
 * TurnTab[dirbase+SRand8()]|flags attribute, LifeA refreshed at the
 * current cell). Otherwise the move commits: LifeA is marked at the new
 * cell and cleared at the old one, AlistX/AlistY/AlistT are updated,
 * and if AlistS is still positive it is decremented and a scent is
 * jammed at the new cell: JamScentRN when the team bit (attribute &
 * 0x80) is set, JamScentBN otherwise. AlistX/AlistY/AlistT/AlistM/
 * AlistS, Dx8/Dy8, TurnTab and Barrier are the exact MAPSYM names from
 * direct_data_bindings and reuse the field layout established by
 * src/recovered/wf_GetAntIndex-a8eba5e594.c and the A-list state used in
 * build/grind/agentU/_DoReturnFoodAnt.c (blocked, same unit). Bounce,
 * SRand8, JamScentRN and JamScentBN reuse src/recovered/wf_Bounce-
 * 0d87abbf42.c, src/recovered/SRand8.c, src/recovered/wf_JamScentRN-
 * 18f9c8a2bb.c and src/recovered/wf_JamScentBN-cd34069882.c; GetNewMode
 * is a unit neighbour (segment 7, far) without an admitted declaration.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char far TurnTab[];
extern int far Barrier;
extern unsigned char near MapA[];
extern unsigned char near LifeA[];

extern int far SRand8(void);
extern int far Bounce(int x, int y);
extern int far GetNewMode(int mode, int attribute);
extern void near JamScentRN(int x, int y, int scent);
extern void near JamScentBN(int x, int y, int scent);

void near DoDigOutAntA(int index)
{
    int x, y;
    int attribute;
    int flags;
    int digmode;
    int dirbase;
    int dirindex;
    unsigned char r;
    int bdir;
    int nx;
    int ny;
    int newtile;
    signed char newattr;

    x = AlistX[index];
    y = AlistY[index];
    attribute = AlistT[index];
    flags = attribute & 0xf8;
    digmode = (attribute & 0x78) >> 3;

    r = SRand8();
    dirbase = (attribute & 7) * 8;
    dirindex = TurnTab[dirbase + r];

    bdir = Bounce(x, y);
    if (bdir != 0)
        dirindex = (bdir - 1) & 7;

    nx = x + (signed char)Dx8[dirindex];
    ny = y + (signed char)Dy8[dirindex];

    if (digmode != 5 && digmode != 9) {
        AlistM[index] = (unsigned char)GetNewMode(digmode, attribute);
        AlistS[index] = 0;
        return;
    }

    if (SRand8() == 0) {
        AlistT[index] = (unsigned char)(attribute - 0x18);
        AlistM[index] = (unsigned char)GetNewMode(digmode, attribute);
        AlistS[index] = 0;
        LifeA[x * 64 + y] = AlistT[index];
        return;
    }

    newtile = MapA[nx * 64 + ny];
    if (newtile > Barrier) {
        newattr = TurnTab[dirbase + SRand8()] | flags;
        AlistT[index] = newattr;
        LifeA[x * 64 + y] = newattr;
        return;
    }

    if (LifeA[nx * 64 + ny] != 0) {
        newattr = TurnTab[dirbase + SRand8()] | flags;
        AlistT[index] = newattr;
        LifeA[x * 64 + y] = newattr;
        return;
    }

    newattr = (unsigned char)dirindex | flags;
    LifeA[nx * 64 + ny] = newattr;
    AlistT[index] = newattr;
    LifeA[x * 64 + y] = 0;
    AlistX[index] = (unsigned char)nx;
    AlistY[index] = (unsigned char)ny;

    if (AlistS[index] != 0) {
        AlistS[index]--;
        if (attribute & 0x80)
            JamScentRN(nx, ny, AlistS[index]);
        else
            JamScentBN(nx, ny, AlistS[index]);
    }
}
