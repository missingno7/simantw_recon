/*
 * PillFoodTile: after two identical IsValidA(x, y) == 1 checks (the target
 * calls IsValidA twice with the same arguments and tests each result with
 * dec/jne), pick x or y by the low bit of the far PillDir word, take that
 * coordinate modulo 6 (signed cdq/idiv), and copy the first byte of that
 * PillarMap row (rows are two bytes: [bx*2 + 0x7c0e]) into the near MapA
 * cell at x*64 + y.  Then, through a saved near pointer to the same cell
 * ([bp-2]), if the cell value is below 0x18 (unsigned), replace it with 0x4b.
 * MapA is the verified near map array; PillDir and PillarMap are far DGROUP
 * objects reached through the segment-9 selector slots, as in ListIndexB.
 */
extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];
extern int far PillDir;
extern unsigned char far PillarMap[][2];

void far PillFoodTile(int x, int y)
{
    unsigned char near *tile;

    if (IsValidA(x, y) == 1) {
        if (IsValidA(x, y) == 1) {
            MapA[x * 64 + y] = PillarMap[((PillDir & 1) ? x : y) % 6][0];
            tile = &MapA[x * 64 + y];
            if (*tile < 0x18)
                *tile = 0x4b;
        }
    }
}
