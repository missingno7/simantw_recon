/*
 * PillFoodTile: if IsValidA(x, y) == 1, then (a) if a second identical
 * IsValidA(x, y) == 1 check passes, select n = x or y by the low bit of the
 * far PillDir word, reduce it modulo 6 (signed cdq/idiv) and copy the first
 * byte of that PillarMap row (two-byte rows) into the near MapA cell
 * x*64 + y; and (b) unconditionally take a near pointer to that MapA cell
 * (stack-homed at [bp-2]) and, if the cell is below 0x18 (unsigned jae),
 * replace it with 0x4b.  The original loads the PillarMap selector after the
 * division but before the row index shift, which suggests the modulo is a
 * separate statement from the array access.  This batch varies that, the
 * register storage class of the tile pointer, and parameter declaration
 * style/order to reproduce x in SI and y in DI.  MapA is the verified near
 * map array; PillDir and PillarMap are far DGROUP objects reached through
 * segment-9 selector slots.
 */
extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];
extern int far PillDir;
extern unsigned char far PillarMap[][2];

void far PillFoodTile(register int x, register int y)
{
    register unsigned char near *tile;

    if (IsValidA(x, y) == 1) {
        if (IsValidA(x, y) == 1) {
            int n;

            if (PillDir & 1)
                n = x;
            else
                n = y;
            n = n % 6;
            MapA[x * 64 + y] = PillarMap[n][0];
        }
        tile = &MapA[x * 64 + y];
        if (*tile < 0x18)
            *tile = 0x4b;
    }
}
