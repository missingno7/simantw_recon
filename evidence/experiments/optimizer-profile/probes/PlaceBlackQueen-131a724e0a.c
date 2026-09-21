/*
 * PlaceBlackQueen: pick a spot for a new black queen's nest and dig it.
 *
 * count = SRand4() + 7 tunnel steps.  Starting at (x=0x20, y=1), if
 * count > y, dig straight down one tile per row y = 1 .. count-1; each
 * row, with 50% chance (SRand2()==0) re-roll a small wobble
 * (SRand1(3)-1, i.e. -1/0/+1); the wobble is then added to the current
 * column when the shifted column stays inside [8,0x38].  Two more tiles
 * are dug diagonally (x++, y++ before each dig, twice), then one more
 * tile at the final (x, y): that spot becomes LastBlackEgg and the
 * reborn point (RebornX/RebornY).  Two columns further east (x+=2, same
 * row) a three-tile queen chamber is dug using the fixed octant 6
 * (Dx8[6]/Dy8[6]), two ants are added at the chamber's two ends with
 * type bytes 0x62 and 0x6a, and BlkQueens is incremented.
 *
 * Profile evidence (agentX): the tunnel loop's range test repeats the
 * sum wobble + x and the column update is x += wobble; only global
 * common-subexpression elimination (/Og, catalog profile "og") folds
 * the three occurrences into the single AX temporary with an unused
 * frame home that the target shows (enter 8, mov ax,di / add ax,si /
 * cmp / cmp / mov si,ax).  Under the og profile this source compiles
 * to the target body byte for byte (x declared before wobble fixes the
 * CSE operand order); under the baseline profile the sum is recomputed.
 * y is the loop row (spilled to [bp-4] inside the loop, DI outside),
 * wobble is a plain local initialised to 0 (home [bp-6]) that takes DI
 * inside the loop, x stays in SI.
 */
extern char far Dx8[];
extern char far Dy8[];
extern int far LastBlackEgg[2];
extern int far RebornX;
extern int far RebornY;
extern int far BlkQueens;

extern void far DigTileB(int x, int y);
extern void far AddAntToBList(int x, int y, int type, int a, int b);
extern int far SRand4(void);
extern int far SRand2(void);
extern int far SRand1(int range);

void far PlaceBlackQueen(void)
{
    int count, x, y, wobble;

    wobble = 0;
    x = 0x20;
    y = 1;
    count = SRand4() + 7;
    if (count > y) {
        do {
            DigTileB(x, y);
            if (SRand2() == 0)
                wobble = SRand1(3) - 1;
            if (wobble + x >= 8 && wobble + x <= 0x38)
                x += wobble;
            y++;
        } while (y < count);
    }

    count = 2;
    do {
        DigTileB(x, y);
        x++;
        y++;
        count--;
    } while (count != 0);

    DigTileB(x, y);
    LastBlackEgg[0] = x;
    LastBlackEgg[1] = y;
    RebornX = x;
    RebornY = y;

    x += 2;
    DigTileB(x, y);
    DigTileB(x + Dx8[6], y + Dy8[6]);
    DigTileB(x + 2 * Dx8[6], y + 2 * Dy8[6]);
    AddAntToBList(x, y, 0x62, 9, 0);
    AddAntToBList(x + Dx8[6], y + Dy8[6], 0x6a, 9, 0);
    BlkQueens++;
}
