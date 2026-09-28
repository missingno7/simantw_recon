/*
 * DoReturnFoodAnt: per-tick step of an A-list ant (index) carrying food
 * home.  x/y/attribute are the ant's AlistX/AlistY/AlistT bytes (one Dx8
 * object, offsets 0x23a4/0x278e/0x2f62; AlistS at 0x334c is the scent
 * charge).  If the ant stands on a nest hole (the IsItHole test written
 * inline: valid cell and MapA tile == 0x50 in the default terrain set or
 * 0x80..0x8f in the alternate set) it enters the nest (GoInNest) and is
 * done; the hole flag and tile are block-scoped locals that live in CX/DX
 * without frame homes.  Otherwise GetNestDir picks the heading toward the nest, Dx8/Dy8
 * step to (nx, ny); a tile above Barrier makes the ant turn in place
 * (TurnTab[dir][SRand8()] | flags).  Otherwise the move is committed:
 * LifeA/AlistT get (ndir | flags), the old cell is cleared and the list
 * coordinates updated; while the scent charge lasts it is decremented and
 * the trail scent of the ant's colour is jammed at the new cell
 * (JamScentRT for red, JamScentBT for black).
 */
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
extern signed char far Dy8[];
extern char far TurnTab[8][8];
extern int far Barrier;
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
    int hole;
    int flags;
    int tile;
    int attribute;
    int ndir;
    int nx, ny;

    x = AT(index + 0x23a4) & 0xff;
    y = AT(index + 0x278e);
    attribute = AT(index + 0x2f62);

    if (!IsValidA(x, y)) {
        hole = 0;
    } else if (TERRAINset == 0) {
        if (MapA[x * 64 + y] == 0x50)
            hole = 1;
        else
            hole = 0;
    } else {
        tile = MapA[x * 64 + y];
        if (tile < 0x80)
            hole = 0;
        else if (tile > 0x8f)
            hole = 0;
        else
            hole = 1;
    }

    if (hole) {
        GoInNest(x, y, index);
        return;
    }

    flags = attribute & 0xf8;
    ndir = GetNestDir(x, y, attribute & 7, attribute);
    nx = x + (signed char)AT(ndir);
    ny = y + Dy8[ndir];

    if (MapA[(nx << 6) + ny] > Barrier) {
        AT(index + 0x2f62) = TurnTab[attribute & 7][SRand8()] | flags;
        LifeA[(x << 6) + y] = AT(index + 0x2f62);
        return;
    }

    LifeA[(nx << 6) + ny] = ndir | flags;
    AT(index + 0x2f62) = ndir | flags;
    LifeA[(x << 6) + y] = 0;
    AT(index + 0x23a4) = nx;
    AT(index + 0x278e) = ny;

    if (AT(index + 0x334c) != 0) {
        AT(index + 0x334c)--;
        if (attribute & 0x80)
            JamScentRT(nx, ny, AT(index + 0x334c));
        else
            JamScentBT(nx, ny, AT(index + 0x334c));
    }
}
