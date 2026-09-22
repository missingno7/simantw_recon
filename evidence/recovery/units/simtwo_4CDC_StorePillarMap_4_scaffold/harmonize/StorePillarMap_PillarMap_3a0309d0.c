/*
 * StorePillarMap: if IsValidA(x, y) == 1, save the MapA cell at x*64 + y
 * (verified near byte array, zero-extended: sub ah,ah / sub ch,ch) into the
 * far word array PillarMap (word store at [bx*2 + 0x7c0e]) at index x % 6
 * when the low bit of the far PillDir word is set, otherwise at index y % 6
 * (signed cdq/idiv).  The two branches are separate statements whose common
 * tail (zero-extend and word store) the compiler merges.  PillDir and
 * PillarMap are far DGROUP objects reached through segment-9 selector slots.
 */
extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];
extern int far PillDir;
extern unsigned char far PillarMap[];

void far StorePillarMap(int x, int y)
{
    if (IsValidA(x, y) == 1) {
        if (PillDir & 1)
            PillarMap[x % 6] = MapA[x * 64 + y];
        else
            PillarMap[y % 6] = MapA[x * 64 + y];
    }
}
