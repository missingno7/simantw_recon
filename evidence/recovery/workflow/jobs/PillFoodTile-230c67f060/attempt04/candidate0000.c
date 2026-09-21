/*
 * PillFoodTile: if IsValidA(x, y) == 1, then (a) if a second identical
 * IsValidA(x, y) == 1 check passes, copy the first byte of the PillarMap row
 * selected by n = (PillDir & 1) ? x : y, n % 6 (rows are two bytes; signed
 * cdq/idiv) into the near MapA cell x*64 + y; and (b) unconditionally, if
 * that MapA cell is below 0x18 (unsigned jae), replace it with 0x4b.  The
 * [bp-2] word holding the cell address is hypothesised to be the compiler's
 * common-subexpression temp for MapA[x*64+y] in the clamp statement, not a
 * declared local; the guarded store lives in another block so it is not
 * merged.  The batch also varies the PillarMap element spelling to reproduce
 * the selector load before the row index.  MapA is the verified near map
 * array; PillDir and PillarMap are far DGROUP objects reached through
 * segment-9 selector slots.
 */
struct PillarEntry {
    unsigned char first;
    unsigned char second;
};

extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];
extern int far PillDir;
extern unsigned char far PillarMap[][2];

void far PillFoodTile(int x, int y)
{
    if (IsValidA(x, y) == 1) {
        if (IsValidA(x, y) == 1) {
            int n;

            if (PillDir & 1)
                n = x;
            else
                n = y;
            MapA[x * 64 + y] = PillarMap[n % 6][0];
        }
        if (MapA[x * 64 + y] < 0x18)
            MapA[x * 64 + y] = 0x4b;
    }
}
