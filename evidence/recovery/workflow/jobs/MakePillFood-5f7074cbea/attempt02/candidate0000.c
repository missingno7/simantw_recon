/*
 * MakePillFood: lay a 6-tile line of pillar food away from the pillar in
 * the direction PillDir selects (0 south/+y, 1 west/-x, 2 north/-y,
 * 3 east/+x). For each of the 6 steps, if IsValidA(x,y) passes twice, the
 * PillarMap byte selected by (PillDir & 1 ? x : y) % 6 is copied into the
 * near MapA cell x*64+y; the cell is then unconditionally raised to food
 * tile 0x4b when it is below 0x18. PillDir/PillarX/PillarY/PillarMap are
 * far DGROUP objects of unit simtwo:4CDC reached through their own
 * segment-9 selector slots (PillarX/PillarY named exactly as in the
 * admitted IsPillDead member of this unit, src/recovered/
 * wf_IsPillDead-8cef0d554b.c); MapA is the near SimAnt map plane.
 */
extern int far PillDir;
extern int far PillarX;
extern int far PillarY;
extern unsigned char far PillarMap[][2];
extern unsigned char near MapA[];
extern int far IsValidA(int x, int y);

void far MakePillFood(void)
{
    int i;
    int x, y;
    unsigned char near *tile;

    switch (PillDir) {
    case 0:
        for (i = 0; i < 6; i++) {
            y = PillarY + i;
            x = PillarX;
            if (IsValidA(x, y) == 1) {
                if (IsValidA(x, y) == 1)
                    MapA[x * 64 + y] = PillarMap[((PillDir & 1) ? x : y) % 6][0];
                tile = &MapA[x * 64 + y];
                if (*tile < 0x18)
                    *tile = 0x4b;
            }
        }
        return;
    case 1:
        for (i = 0; i < 6; i++) {
            y = PillarY;
            x = PillarX - i;
            if (IsValidA(x, y) == 1) {
                if (IsValidA(x, y) == 1)
                    MapA[x * 64 + y] = PillarMap[((PillDir & 1) ? x : y) % 6][0];
                tile = &MapA[x * 64 + y];
                if (*tile < 0x18)
                    *tile = 0x4b;
            }
        }
        return;
    case 2:
        for (i = 0; i < 6; i++) {
            y = PillarY - i;
            x = PillarX;
            if (IsValidA(x, y) == 1) {
                if (IsValidA(x, y) == 1)
                    MapA[x * 64 + y] = PillarMap[((PillDir & 1) ? x : y) % 6][0];
                tile = &MapA[x * 64 + y];
                if (*tile < 0x18)
                    *tile = 0x4b;
            }
        }
        return;
    case 3:
        for (i = 0; i < 6; i++) {
            y = PillarY;
            x = PillarX + i;
            if (IsValidA(x, y) == 1) {
                if (IsValidA(x, y) == 1)
                    MapA[x * 64 + y] = PillarMap[((PillDir & 1) ? x : y) % 6][0];
                tile = &MapA[x * 64 + y];
                if (*tile < 0x18)
                    *tile = 0x4b;
            }
        }
        return;
    }
}
