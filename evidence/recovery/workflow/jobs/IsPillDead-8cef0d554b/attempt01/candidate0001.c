/*
 * IsPillDead: report whether the pillar is overrun.  The 3x3 block of
 * cells around the far PillarX/PillarY position is scanned; every valid
 * cell (IsValidA) holding an ant in the near LifeA map counts, and more
 * than five such cells means the pillar is dead.
 */
extern unsigned char near LifeA[128][64];
extern int far PillarX;
extern int far PillarY;
extern int far IsValidA(int x, int y);

int far IsPillDead(void)
{
    int x;
    int y;
    int count;

    count = 0;
    for (x = PillarX - 1; x < PillarX + 2; x++) {
        for (y = PillarY - 1; y < PillarY + 2; y++) {
            if ((IsValidA(x, y) ? LifeA[x][y] : 0))
                count++;
        }
    }
    return count > 5;
}
