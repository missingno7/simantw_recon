/*
 * PlaceRedQueen: pick a spot for a new red queen's nest and dig it.
 * Red twin of PlaceBlackQueen, minus the 50% SRand2() gate on the
 * tunnel's wobble re-roll (here every row re-rolls) and minus the
 * separate RebornX/RebornY stores (only LastRedEgg is recorded).
 *
 * count = SRand4() + 7 tunnel steps.  If count > 1, dig straight down
 * column x=0x20 from row 1, one tile per row; each row a small wobble
 * (SRand1(3)-1, i.e. -1/0/+1) is re-rolled and added to the current
 * column, and if the result stays inside [8,0x38] it becomes the new
 * column (otherwise the column is left where it was).  After the
 * tunnel, y is the row just past its last dug tile (whether or not the
 * tunnel ran at all: if count<=1 nothing is dug and x=0x20, y=1 are the
 * untouched initial values).  Two more tiles are then dug diagonally
 * (x++, y++ before each dig, twice), then one more tile at the final
 * (x, y): that spot becomes LastRedEgg.  Two columns further east
 * (x+=2, same row) a three-tile queen chamber is dug using the fixed
 * octant 6 (Dx8[6]/Dy8[6], MakeRedQueen's own pattern with dir=2,
 * d=dir^4=6 baked in rather than computed), two ants are added at the
 * chamber's two ends with type bytes dir+0xE0 and dir+0xE8, and
 * RedQueens is incremented.
 */
extern char far Dx8[];
extern char far Dy8[];
extern int far LastRedEgg[2];
extern int far RedQueens;

extern void far DigTileR(int x, int y);
extern void far AddAntToRList(int x, int y, int type, int a, int b);
extern int far SRand4(void);
extern int far SRand1(int range);

void far PlaceRedQueen(void)
{
    int wobble, i, count, cand, x, y;

    wobble = 0;
    x = 0x20;
    i = 1;
    count = SRand4() + 7;
    if (count > i) {
        do {
            DigTileR(x, i);
            wobble = SRand1(3) - 1;
            cand = wobble + x;
            if (cand >= 8 && cand <= 0x38)
                x = cand;
            i++;
        } while (i < count);
    }
    y = i;

    count = 2;
    do {
        DigTileR(x, y);
        x++;
        y++;
        count--;
    } while (count != 0);

    DigTileR(x, y);
    LastRedEgg[0] = x;
    LastRedEgg[1] = y;

    x += 2;
    DigTileR(x, y);
    DigTileR(x + Dx8[6], y + Dy8[6]);
    DigTileR(x + 2 * Dx8[6], y + 2 * Dy8[6]);
    AddAntToRList(x, y, 0xe2, 9, 0);
    AddAntToRList(x + Dx8[6], y + Dy8[6], 0xea, 9, 0);
    RedQueens++;
}
