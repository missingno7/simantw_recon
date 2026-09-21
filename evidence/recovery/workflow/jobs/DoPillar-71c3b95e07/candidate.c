/*
 * DoPillar: per-tick pillar update for unit simtwo:4CDC.
 *
 * If TERRAINset is active, do nothing. Otherwise call DoSow(); if no
 * pillar exists yet (Dx8==0) create one via MakeAPill(), mark it active
 * and arm the growth timer PillarSeg=4, then return.
 *
 * Otherwise: PillDir selects a compass leg (0: +y, 1: -x, 2: -y, 3: +x).
 * The tile on the OPPOSITE side is checked for an ant (LifeA, via
 * IsValidA); if one is there, the admitted IsPillDead 3x3-neighbourhood
 * ant count around (PillarX,PillarY) is inlined, and if the pillar is
 * overrun (count>5) Dx8 is reset and MakePillFood() is called; either
 * way the tick then returns.
 *
 * If no ant blocks it: PillarSeg is decremented. At the tip of the
 * reach (PillarSeg+1 cells out along PillDir's leg), the parked
 * ReplacePillarMap body is inlined once PillarSeg has counted back down
 * to 4; on every other tick a single tile ('m' for the +-y legs, 'j' for
 * the +-x legs) is written there instead if the tip is valid. A second,
 * unconditional pass writes another tile ('n' for the +-y legs, 'j' for
 * the +-x legs) PillarSeg cells out (no +1).
 *
 * Once PillarSeg has counted all the way down to 0, the pillar itself
 * steps one cell along its leg. After re-checking PillarX/PillarY stay
 * inside the map's padded bounds (else Dx8 is reset and the tick
 * returns), the parked StorePillarMap body is inlined at the pillar's
 * own new cell, a final directional tile pair is written around it, the
 * timer is rearmed to 5, and the tick returns.
 *
 * Declarations reuse the admitted IsPillDead member of this unit
 * (src/recovered/wf_IsPillDead-8cef0d554b.c: LifeA, PillarX, PillarY,
 * IsValidA) and the far-object identities of the parked exact
 * StorePillarMap/ReplacePillarMap bodies of this unit
 * (evidence/recovery/body-solved/: PillDir, PillarMap, MapA). Dx8,
 * PillarSeg and TERRAINset are this unit's remaining named far objects
 * (this packet's direct_data_bindings).
 */
extern int far TERRAINset;
extern int far Dx8;
extern int far PillarSeg;
extern int far PillDir;
extern int far PillarX;
extern int far PillarY;
extern unsigned char near LifeA[128][64];
extern unsigned char far PillarMap[][2];
extern unsigned char near MapA[];
extern int far IsValidA(int x, int y);
extern void far DoSow(void);
extern void far MakeAPill(void);
extern void far MakePillFood(void);

void far DoPillar(void)
{
    int cx, cy;
    int x, y, count;
    int gx, gy;
    int hx, hy;

    if (TERRAINset == 1)
        return;
    DoSow();
    if (Dx8 == 0) {
        MakeAPill();
        Dx8 = 1;
        PillarSeg = 4;
        return;
    }

    switch (PillDir) {
    case 0:
        cy = PillarY - 1;
        cx = PillarX;
        break;
    case 1:
        cy = PillarY;
        cx = PillarX + 1;
        break;
    case 2:
        cy = PillarY + 1;
        cx = PillarX;
        break;
    case 3:
        cy = PillarY;
        cx = PillarX - 1;
        break;
    }
    if ((IsValidA(cx, cy) == 0 ? 0 : LifeA[cx][cy]) != 0) {
        count = 0;
        for (x = PillarX - 1; x < PillarX + 2; x++)
            for (y = PillarY - 1; y < PillarY + 2; y++)
                if ((IsValidA(x, y) == 0 ? 0 : LifeA[x][y]) != 0)
                    count++;
        if (count > 5) {
            Dx8 = 0;
            MakePillFood();
        }
        return;
    }

    PillarSeg--;
    if (PillarSeg == 4) {
        switch (PillDir) {
        case 0:
            gy = PillarY + PillarSeg + 1;
            gx = PillarX;
            break;
        case 1:
            gy = PillarY;
            gx = PillarX - PillarSeg - 1;
            break;
        case 2:
            gy = PillarY - PillarSeg - 1;
            gx = PillarX;
            break;
        case 3:
            gy = PillarY;
            gx = PillarX + PillarSeg + 1;
            break;
        }
        if (IsValidA(gx, gy) == 1) {
            if (PillDir & 1) {
                MapA[gx * 64 + gy] = PillarMap[gx % 6][0];
            } else {
                MapA[gx * 64 + gy] = PillarMap[gy % 6][0];
            }
        }
    } else {
        switch (PillDir) {
        case 0:
            gy = PillarY + PillarSeg + 1;
            gx = PillarX;
            break;
        case 1:
            gy = PillarY;
            gx = PillarX - PillarSeg - 1;
            break;
        case 2:
            gy = PillarY - PillarSeg - 1;
            gx = PillarX;
            break;
        case 3:
            gy = PillarY;
            gx = PillarX + PillarSeg + 1;
            break;
        }
        if (IsValidA(gx, gy) == 1)
            MapA[gx * 64 + gy] = (PillDir & 1) ? 'j' : 'm';
    }

    switch (PillDir) {
    case 0:
        hy = PillarY + PillarSeg;
        hx = PillarX;
        break;
    case 1:
        hy = PillarY;
        hx = PillarX - PillarSeg;
        break;
    case 2:
        hy = PillarY - PillarSeg;
        hx = PillarX;
        break;
    case 3:
        hy = PillarY;
        hx = PillarX + PillarSeg;
        break;
    }
    if (IsValidA(hx, hy) == 1)
        MapA[hx * 64 + hy] = (PillDir & 1) ? 'j' : 'n';

    if (PillarSeg != 0)
        return;

    switch (PillDir) {
    case 0:
        PillarY--;
        break;
    case 1:
        PillarX++;
        break;
    case 2:
        PillarY++;
        break;
    case 3:
        PillarX--;
        break;
    }

    if (PillarX < -6 || PillarX > 0x86 || PillarY < -6 || PillarY > 0x45) {
        Dx8 = 0;
        return;
    }

    if (IsValidA(PillarX, PillarY) == 1) {
        if (PillDir & 1) {
            PillarMap[PillarX % 6][0] = MapA[PillarX * 64 + PillarY];
            PillarMap[PillarX % 6][1] = 0;
        } else {
            PillarMap[PillarY % 6][0] = MapA[PillarX * 64 + PillarY];
            PillarMap[PillarY % 6][1] = 0;
        }
    }

    switch (PillDir) {
    case 0:
        if (IsValidA(PillarX, PillarY) == 1)
            MapA[PillarX * 64 + PillarY] = 'l';
        if (IsValidA(PillarX, PillarY + 1) == 1)
            MapA[PillarX * 64 + PillarY + 1] = 'm';
        break;
    case 1:
        if (IsValidA(PillarX, PillarY) == 1)
            MapA[PillarX * 64 + PillarY] = 'k';
        if (IsValidA(PillarX - 1, PillarY) == 1)
            MapA[(PillarX - 1) * 64 + PillarY] = 'i';
        break;
    case 2:
        if (IsValidA(PillarX, PillarY) == 1)
            MapA[PillarX * 64 + PillarY] = 'o';
        if (IsValidA(PillarX, PillarY - 1) == 1)
            MapA[PillarX * 64 + PillarY - 1] = 'm';
        break;
    case 3:
        if (IsValidA(PillarX, PillarY) == 1)
            MapA[PillarX * 64 + PillarY] = 'h';
        if (IsValidA(PillarX + 1, PillarY) == 1)
            MapA[(PillarX + 1) * 64 + PillarY] = 'i';
        break;
    }

    PillarSeg = 5;
}
