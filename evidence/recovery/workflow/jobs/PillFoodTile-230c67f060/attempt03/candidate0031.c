/*
 * PillFoodTile: if IsValidA(x, y) == 1, then (a) if a second identical
 * IsValidA(x, y) == 1 check passes, copy the first byte of the PillarMap row
 * selected by ((PillDir & 1) ? x : y) % 6 (rows are two bytes; signed
 * cdq/idiv) into the near MapA cell x*64 + y; and (b) unconditionally take a
 * near pointer to that MapA cell ([bp-2]) and, if the cell is below 0x18
 * (unsigned jae), replace it with 0x4b.  The second guard's failing branch
 * lands on the pointer computation, so the guarded store and the pointer
 * computation are separate statements.  This batch varies how the selected
 * coordinate and the tile pointer are spelled and how the parameters are
 * declared, to reproduce x in SI / y in DI and no ternary temp spill.
 * MapA is the verified near map array; PillDir and PillarMap are far DGROUP
 * objects reached through segment-9 selector slots.
 */
extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];
extern int far PillDir;
extern unsigned char far PillarMap[][2];

void far PillFoodTile(register int x, register int y)
{
    unsigned char near *tile;

    if (IsValidA(x, y) == 1) {
        if (IsValidA(x, y) == 1)
            MapA[x * 64 + y] = ((unsigned char far *)PillarMap)[(((PillDir & 1) ? x : y) % 6) * 2];
        tile = MapA + x * 64 + y;
        if (*tile < 0x18)
            *tile = 0x4b;
    }
}
