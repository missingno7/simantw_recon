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
