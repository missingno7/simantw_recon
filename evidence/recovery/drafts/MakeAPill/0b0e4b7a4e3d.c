/*
 * MakeAPill: create a new pillar. Roll a random compass leg PillDir =
 * SRand1(4) (0: +y/south, 1: -x/west, 2: -y/north, 3: +x/east, matching
 * this unit's other members). Per leg, the pillar starts at a random
 * position along the corresponding map edge (the far coordinate on that
 * edge is fixed; the near one is SRand1-rolled): south y=63/x random 0-
 * 127, west x=0/y random 0-63, north y=0/x random 0-127, east
 * x=127/y random 0-63. If the starting cell is valid, the admitted
 * StorePillarMap body is inlined there (save the terrain under the new
 * pillar into PillarMap); a second, independent IsValidA check then
 * writes the pillar's own visible tile there ('l'/'k'/'o'/'h' for
 * south/west/north/east).
 *
 * Declarations reuse the admitted IsPillDead member of this unit
 * (src/recovered/wf_IsPillDead-8cef0d554b.c: PillarX, PillarY,
 * IsValidA) and the far-object identities of the parked exact
 * StorePillarMap body of this unit (evidence/recovery/body-solved/
 * _StorePillarMap-5dc9f78b9b44.c: PillDir int far, PillarMap int far[],
 * MapA near byte array).
 */
extern int far PillDir;
extern int far PillarX;
extern int far PillarY;
extern int far PillarMap[];
extern unsigned char near MapA[];
extern int far IsValidA(int x, int y);
extern int far SRand1(int limit);

void far MakeAPill(void)
{
    PillDir = SRand1(4);
    switch (PillDir) {
    case 0:
        PillarX = SRand1(0x80);
        PillarY = 0x3f;
        if (IsValidA(PillarX, PillarY) == 1) {
            if (PillDir & 1)
                PillarMap[PillarX % 6] = MapA[PillarX * 64 + PillarY];
            else
                PillarMap[PillarY % 6] = MapA[PillarX * 64 + PillarY];
        }
        if (IsValidA(PillarX, PillarY) == 1)
            MapA[PillarX * 64 + PillarY] = 'l';
        return;
    case 1:
        PillarY = SRand1(0x40);
        PillarX = 0;
        if (IsValidA(PillarX, PillarY) == 1) {
            if (PillDir & 1)
                PillarMap[PillarX % 6] = MapA[PillarX * 64 + PillarY];
            else
                PillarMap[PillarY % 6] = MapA[PillarX * 64 + PillarY];
        }
        if (IsValidA(PillarX, PillarY) == 1)
            MapA[PillarX * 64 + PillarY] = 'k';
        return;
    case 2:
        PillarX = SRand1(0x80);
        PillarY = 0;
        if (IsValidA(PillarX, PillarY) == 1) {
            if (PillDir & 1)
                PillarMap[PillarX % 6] = MapA[PillarX * 64 + PillarY];
            else
                PillarMap[PillarY % 6] = MapA[PillarX * 64 + PillarY];
        }
        if (IsValidA(PillarX, PillarY) == 1)
            MapA[PillarX * 64 + PillarY] = 'o';
        return;
    case 3:
        PillarX = 0x7f;
        PillarY = SRand1(0x40);
        if (IsValidA(PillarX, PillarY) == 1) {
            if (PillDir & 1)
                PillarMap[PillarX % 6] = MapA[PillarX * 64 + PillarY];
            else
                PillarMap[PillarY % 6] = MapA[PillarX * 64 + PillarY];
        }
        if (IsValidA(PillarX, PillarY) == 1)
            MapA[PillarX * 64 + PillarY] = 'h';
        return;
    }
}

/* Round 2, variant 3: controlled source-shape hypothesis. */
