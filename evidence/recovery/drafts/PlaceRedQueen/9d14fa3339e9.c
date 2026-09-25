/*
 * PlaceRedQueen: pick a spot for a new red queen's nest and dig it.
 * Twin of PlaceBlackQueen without the SRand2 gate: count = SRand4() + 7
 * tunnel steps; starting at (x=0x20, y=1), if count > y dig one tile per
 * row y = 1 .. count-1, re-rolling the column wobble (SRand1(3)-1, i.e.
 * -1/0/+1) every row and shifting the column by it whenever the shifted
 * column stays inside [8,0x38].  Then two diagonal tiles (x++, y++
 * before each dig), one more tile at the final (x, y) which becomes
 * LastRedEgg, and two columns east a three-tile chamber along the fixed
 * octant 6 (Dx8[6]/Dy8[6]) with two ants of type bytes 0xe2/0xea; then
 * RedQueens is incremented.
 *
 * Profile evidence (agentX): as in PlaceBlackQueen, the range test
 * repeats the sum wobble + x and the update is x += wobble; only global
 * CSE (/Og, catalog profile "og") folds them into the single AX
 * temporary with an unused frame home (enter 6: count, y spill, temp).
 * Under og this source matches every non-fixup byte of the target
 * (116/117 opcodes, the candidate only adds the trailing alignment nop);
 * under the baseline profile the sum is recomputed (115/119).
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
    int count, x, y, wobble;

    x = 0x20;
    y = 1;
    count = SRand4() + 7;
    if (count > y) {
        do {
            DigTileR(x, y);
            wobble = SRand1(3) - 1;
            if (wobble + x >= 8 && wobble + x <= 0x38)
                x += wobble;
            y++;
        } while (y < count);
    }

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
