/* Candidate translation unit simtwo_4CDC_StorePillarMap_4_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _StorePillarMap, _ReplacePillarMap, _PillGetLife, _IsPillDead
 * SCAFFOLDED: unclaimed members _DoPillar are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];
extern int far PillDir;
extern int far PillarMap[];
extern unsigned char near LifeA[128][64];
extern int far PillarX;
extern int far PillarY;

extern int far TERRAINset;  /* scaffold reference for pool word C59A (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx8;  /* scaffold reference for pool word C59C (segment 8, MAPSYM_SITE_NAME) */
extern int far PillarSeg;  /* scaffold reference for pool word C59E (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_DoPillar(void);
int PillGetLife(int x, int y);
int far IsPillDead(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoPillar)
#pragma alloc_text(RUN2_TEXT, PillGetLife, IsPillDead)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoPillar.
 * It only reproduces the object's selector-pool allocation order for the
 * words C59A C59C C59E C5A0 C5A2 C5A4 C5A6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoPillar(void)
{
    volatile int t;

    t = TERRAINset;
    t = Dx8;
    t = PillarSeg;
    t = (int)PillDir;
    t = (int)PillarY;
    t = (int)PillarX;
    t = PillarMap[0];
}

void far StorePillarMap(int x, int y)
{
    if (IsValidA(x, y) == 1) {
        if (PillDir & 1)
            PillarMap[x % 6] = MapA[x * 64 + y];
        else
            PillarMap[y % 6] = MapA[x * 64 + y];
    }
}

#define PillDir (*(unsigned char far *)&PillDir)  /* shape view of the unit declaration for this member only */
#define PillarMap ((unsigned char far *)PillarMap)  /* shape view of the unit declaration for this member only */
void far ReplacePillarMap(int x, int y)
{
    if (IsValidA(x, y) != 1)
        return;
    if (PillDir & 1)
        MapA[(x << 6) + y] = PillarMap[(x % 6) << 1];
    else
        MapA[(x << 6) + y] = PillarMap[(y % 6) << 1];
}
#undef PillDir
#undef PillarMap

#define LifeA ((unsigned char near *)LifeA)  /* shape view of the unit declaration for this member only */
int PillGetLife(int x, int y)
{
    if (!IsValidA(x, y))
        return;
    return LifeA[x * 64 + y];
}
#undef LifeA

int far IsPillDead(void)
{
    int x;
    int y;
    int count;

    count = 0;
    for (x = PillarX - 1; x < PillarX + 2; x++) {
        for (y = PillarY - 1; y < PillarY + 2; y++) {
            if ((IsValidA(x, y) == 0 ? 0 : LifeA[x][y]) != 0)
                count++;
        }
    }
    return count > 5;
}

