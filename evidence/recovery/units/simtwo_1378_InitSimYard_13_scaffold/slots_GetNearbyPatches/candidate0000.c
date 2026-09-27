/*
 * GetNearbyPatches: inspect the six nearby patch offsets (private byte
 * tables PatchX/PatchY), retain only coordinates inside the 12 by 16 local
 * map, and score the black/red population planes: +3 for an occupied
 * black cell, -3 for an occupied red cell.
 *
 * Binding: YMapPopB (MAPSYM seg8:0xA4) and YMapPopR (seg8:0x164) are two
 * 12x16 byte maps indexed (x << 4) + y; each symbol carries its own base
 * displacement, so the index is the bare cell offset with no constant
 * (the previous +0xA4/+0x164 doubled the base).  Each map is addressed
 * through its own selector word (C564 for B, C562 for R).
 *
 * Unit review (simtwo:1378): PatchX/PatchY are private byte tables of the
 * object (DGROUP 0x25DC/0x25E2, no MAPSYM name), so they are static data of
 * the unit with the image bytes, not externs.
 */
static unsigned char PatchX[6] = { 0, 1, 0, 0xff, 0, 0 };
static unsigned char PatchY[6] = { 0xff, 0, 1, 0, 0, 0 };
extern unsigned char far YMapPopB[];
extern unsigned char far YMapPopR[];

int far GetNearbyPatches(int x, int y)
{
    int index;
    register int offset;
    int count;
    register int patchX;
    register int patchY;

    count = 0;
    for (index = 0; index < 6; ++index) {
        patchY = PatchY[index] + y;
        patchX = PatchX[index] + x;
        if (patchX >= 0 && patchY >= 0 &&
            patchX < 12 && patchY < 16) {
            offset = (patchX << 4) + patchY;
            if (YMapPopB[(patchX << 4) + patchY] != 0)
                count += 3;
            if (YMapPopR[(patchX << 4) + patchY] != 0)
                count -= 3;
        }
    }
    return count;
}
