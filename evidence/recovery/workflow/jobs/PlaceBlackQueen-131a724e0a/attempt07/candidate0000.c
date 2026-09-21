/*
 * PlaceBlackQueen: pick a spot for a new black queen's nest and dig it.
 *
 * count = SRand4() + 7 tunnel steps.  Starting at (x=0x20, y=1), if
 * count > y, dig straight down one tile per row i = y .. count-1; each
 * row, with 50% chance (SRand2()==0) re-roll a small wobble
 * (SRand1(3)-1, i.e. -1/0/+1) that is then added to the current column
 * and, if the result stays inside [8,0x38], becomes the new column.
 * After the tunnel y becomes the row just past the last dug tile (only
 * when the tunnel ran; otherwise y stays 1).  Two more tiles are dug
 * diagonally (x++, y++ before each dig, twice), then one more tile at
 * the final (x, y): that spot becomes LastBlackEgg and the reborn point
 * (RebornX/RebornY).  Two columns further east (x+=2, same row) a
 * three-tile queen chamber is dug using the fixed octant 6 (Dx8[6]/
 * Dy8[6]), two ants are added at the chamber's two ends with type bytes
 * 0x62 and 0x6a, and BlkQueens is incremented.
 *
 * Frame/register hypothesis (agentX, reissue 1): the target keeps x in
 * SI and y in DI for the whole function (mov si,20h / mov di,1 / cmp
 * ax,di), copies y into a memory row counter i ([bp-4]) only inside the
 * "if (count > y)" arm, hoists the plain local wobble from its memory
 * home [bp-6] into DI at loop entry (DI is free there because y is dead
 * until "y = i" after the loop), and stores y = i back into DI after the
 * loop.  count is [bp-2].  So y is a distinct variable from i, the loop
 * is a do-while guarded by count > y, and the memory locals are declared
 * in the order count, i, wobble.
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
    int count, i, wobble, x, y, cand;

    wobble = 0;
    x = 0x20;
    y = 1;
    count = SRand4() + 7;
    if (count > y) {
        i = y;
        do {
            DigTileB(x, i);
            if (SRand2() == 0) {
                wobble = SRand1(3);
                wobble--;
            }
            cand = wobble + x;
            if (cand >= 8 && cand <= 0x38)
                x = cand;
            i++;
        } while (i < count);
        y = i;
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
