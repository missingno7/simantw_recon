/* First movement pass: periodic yard guard, then probe the four adjacent tiles. */
extern int __based(__segname("PACK")) YardCycle;
extern int __based(__segname("PACK")) BoyPx;
extern int __based(__segname("PACK")) BoyPy;
extern char far Dx8[];
extern char far Dy8[];

extern int far SRand1(int range);
extern int far IsClearTile(int plane, int x, int y);
extern void far FootFall(int x, int y);
extern void far KillSpider(int x, int y);
extern void far YellowDeath(int x, int y);

void far SimKidOutside(void)
{
    int x;
    int y;
    int direction;
    int nextX;
    int nextY;
    int moved;

    if ((YardCycle & 3) == 0)
        return;

    x = BoyPx;
    y = BoyPy;
    moved = 0;
    for (direction = 3; direction >= 0; direction--) {
        nextX = x + Dx8[direction];
        nextY = y + Dy8[direction];
        if (nextX < 0 || nextX > 11 || nextY < 0 || nextY > 15)
            continue;
        if (IsClearTile(1, nextX, nextY)) {
            if (SRand1(4) == 0)
                continue;
            BoyPx = nextX;
            BoyPy = nextY;
            FootFall(nextX, nextY);
            moved = 1;
            break;
        }
    }

    if (moved) {
        KillSpider(BoyPx, BoyPy);
        YellowDeath(BoyPx, BoyPy);
    }
}
