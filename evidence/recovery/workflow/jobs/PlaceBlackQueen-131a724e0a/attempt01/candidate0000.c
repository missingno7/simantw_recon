/*
 * PlaceBlackQueen: pick a spot for a new black queen's nest and dig it.
 *
 * count = SRand4() + 7 tunnel steps.  If count > 1, dig straight down
 * column x=0x20 from row 1, one tile per row; each row, with 50% chance
 * (SRand2()==0) re-roll a small wobble (SRand1(3)-1, i.e. -1/0/+1) that
 * is then added to the current column and, if the result stays inside
 * [8,0x38], becomes the new column (otherwise the column is left where
 * it was and the stale wobble is tried again next row).  After the
 * tunnel, y is the row just past its last dug tile (whether or not the
 * tunnel ran at all: if count<=1 nothing is dug and x=0x20, y=1 are the
 * untouched initial values).  Two more tiles are then dug diagonally
 * (x++, y++ before each dig, twice), then one more tile at the final
 * (x, y): that spot becomes both LastBlackEgg and the reborn point
 * (RebornX/RebornY).  Two columns further east (x+=2, same row) a
 * three-tile queen chamber is dug using the fixed octant 6 (Dx8[6]/
 * Dy8[6], i.e. MakeBlkQueen's own pattern with dir=2, d=dir^4=6 baked
 * in rather than computed), two ants are added at the chamber's two
 * ends with type bytes dir+0x60 and dir+0x68, and BlkQueens is
 * incremented.
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
    int wobble, i, count, cand, x, y;

    wobble = 0;
    x = 0x20;
    count = SRand4() + 7;
    if (count > 1) {
        i = 1;
        do {
            DigTileB(x, i);
            if (SRand2() == 0)
                wobble = SRand1(3) - 1;
            cand = x + wobble;
            if (cand >= 8 && cand <= 0x38)
                x = cand;
            i++;
        } while (i < count);
        y = i;
    } else {
        y = 1;
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
