/* Candidate translation unit simtwo_4CDC_StorePillarMap_4_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _StorePillarMap, _ReplacePillarMap, _PillGetLife, _IsPillDead
 * SCAFFOLDED: unclaimed members _DoPillar are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];
extern int far PillDir;
extern unsigned char far PillarMap[][2];
extern unsigned char near LifeA[128][64];
extern int far PillarX;
extern int far PillarY;

extern int far TERRAINset;  /* scaffold reference for pool word C59A (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx8;  /* scaffold reference for pool word C59C (segment 8, MAPSYM_SITE_NAME) */
extern int far match_position;  /* scaffold reference for pool word C59E (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DoPillar(void);
int PillGetLife(int x, int y);
int far IsPillDead(void);

void PlacePillTile(int x, int y, int value);
void far MakePillFood(void);
void far PillFoodTile(int x, int y);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoPillar)
#pragma alloc_text(RUN2_TEXT, PlacePillTile, PillGetLife, IsPillDead, MakePillFood, PillFoodTile)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoPillar.
 * It only reproduces the object's selector-pool allocation order for the
 * words C59A C59C C59E C5A0 C5A2 C5A4 C5A6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoPillar(void)
{
    volatile int t;

    t = TERRAINset;
    t = Dx8;
    t = match_position;
    t = (int)PillDir;
    t = (int)PillarY;
    t = (int)PillarX;
    t = PillarMap[0][0];
}

#define PillarMap ((int far *)PillarMap)  /* byte-array declaration view for this member only */
void far StorePillarMap(int x, int y)
{
    if (IsValidA(x, y) == 1) {
        if (PillDir & 1)
            PillarMap[x % 6] = MapA[x * 64 + y];
        else
            PillarMap[y % 6] = MapA[x * 64 + y];
    }
}
#undef PillarMap

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

void PlacePillTile(int x, int y, int value)
{
    if (IsValidA(x, y) == 1)
        MapA[x * 64 + y] = (unsigned char)value;
}

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

void far MakePillFood(void)
{
    int i;
    int tileIndex;

    switch (PillDir) {
    case 0:
        for (i = 0; i < 6; i++) {
            int x, y;
            y = PillarY + i;
            x = PillarX;
            if (IsValidA(x, y) == 1) {
                if (IsValidA(x, y) == 1) {
                    if (PillDir & 1)
                        MapA[x * 64 + y] = PillarMap[x % 6][0];
                    else
                        MapA[x * 64 + y] = PillarMap[y % 6][0];
                }
                if (MapA[x * 64 + y] < 0x18)
                    MapA[x * 64 + y] = 0x4b;
            }
        }
        return;
    case 1:
        for (i = 0; i < 6; i++) {
            int x, y;
            y = PillarY;
            x = PillarX - i;
            if (IsValidA(x, y) == 1) {
                if (IsValidA(x, y) == 1) {
                    if (PillDir & 1)
                        MapA[x * 64 + y] = PillarMap[x % 6][0];
                    else
                        MapA[x * 64 + y] = PillarMap[y % 6][0];
                }
                if (MapA[x * 64 + y] < 0x18)
                    MapA[x * 64 + y] = 0x4b;
            }
        }
        return;
    case 2:
        for (i = 0; i < 6; i++) {
            int x, y;
            y = PillarY - i;
            x = PillarX;
            if (IsValidA(x, y) == 1) {
                if (IsValidA(x, y) == 1) {
                    if (PillDir & 1)
                        MapA[x * 64 + y] = PillarMap[x % 6][0];
                    else
                        MapA[x * 64 + y] = PillarMap[y % 6][0];
                }
                if (MapA[x * 64 + y] < 0x18)
                    MapA[x * 64 + y] = 0x4b;
            }
        }
        return;
    case 3:
        for (i = 0; i < 6; i++) {
            int x, y;
            y = PillarY;
            x = PillarX + i;
            if (IsValidA(x, y) == 1) {
                if (IsValidA(x, y) == 1) {
                    if (PillDir & 1)
                        MapA[x * 64 + y] = PillarMap[x % 6][0];
                    else
                        MapA[x * 64 + y] = PillarMap[y % 6][0];
                }
                if (MapA[x * 64 + y] < 0x18)
                    MapA[x * 64 + y] = 0x4b;
            }
        }
        return;
    }
}

void far PillFoodTile(int x, int y)
{
    if (IsValidA(x, y) == 1) {
        if (IsValidA(x, y) == 1) {
            if (PillDir & 1)
                MapA[x * 64 + y] = ((unsigned char far *)PillarMap)
                    [2 * (x % 6)];
            else
                MapA[x * 64 + y] = ((unsigned char far *)PillarMap)
                    [2 * (y % 6)];
        }
        if (MapA[x * 64 + y] < 0x18)
            MapA[x * 64 + y] = 0x4b;
    }
}
