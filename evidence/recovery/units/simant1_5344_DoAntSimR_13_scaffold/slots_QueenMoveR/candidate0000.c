/* Candidate translation unit simant1_5344_DoAntSimR_11_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoAntSimR, _RaidInR, _StayInR, _RaidOutR, _DoRestR, _DoRandR, _DoNestFightR, _CheckNestFightR, _SimEggR, _QueenMoveR, _KillTailR, _LostHeadR, _LostTailR, _TryMoveDirR, _TryEatFoodR, _EatFoodR, _StealFoodR, _DecEatR
 * SCAFFOLDED: unclaimed members _DoNestAntR and _SimQueenR are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far ListIndexR;
extern int far Tindex;
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern int far TileMassYR;
extern int far TileMassXR;
extern int near GetBestDir(int kind, int x, int y, int targetX, int targetY);
extern void far DoNestAntR(int life, int column, int attribute);
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int far FoodR;
extern int far SRand8(void);
extern int far SRand1(int range);
extern int far SRand16(void);
extern int far GetEnterDirR(int x, int y, int dir);
extern int far TryMoveDirR(int x, int y, int dir);
extern int near GetOutR(int x);
extern int far GetExitDirR(int x, int y, int limit);
struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far RlistX;
#define RlistY RlistX.y
#define RlistM RlistX.m
#define RlistS RlistX.s
#define RlistT RlistX.t
extern int near MeColor;
extern int far OptionStates[];
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far GetNewMode(int caste, int type);
extern void far RestBalloons(int x, int y, int plane);
extern int far SRand32(void);
extern void far AddAntToRList(int life, int column, int attribute, int state, int direction);
extern void far FightBalloons(int x, int y, int kind);
extern unsigned char near CasteModeTab[];
extern int far GetNewModeR(int mode);
extern int far Cycle;
extern int far StrategicModeR;
extern char far CasteTabC[];
extern void far EggBalloons(int x, int y, int plane);
extern int far EatCountR;
extern int near CastePopR[];
extern int near RpopT;
extern int near HealthR;

extern int far TemRModePop;  /* scaffold reference for pool word C388 (segment 9, MAPSYM_SITE_NAME) */
extern int far RAntsExpired;  /* scaffold reference for pool word C38A (segment 9, MAPSYM_SITE_NAME) */
extern int far FlyAwayR;  /* scaffold reference for pool word C38E (segment 9, MAPSYM_SITE_NAME) */
extern int far BAntsExpired;  /* scaffold reference for pool word C390 (segment 9, MAPSYM_SITE_NAME) */
extern int far TemBModePop;  /* scaffold reference for pool word C392 (segment 9, MAPSYM_SITE_NAME) */
extern int far RedQueens;  /* scaffold reference for pool word C3A0 (segment 9, MAPSYM_SITE_NAME) */
extern int far LastRedEgg;  /* scaffold reference for pool word C3A2 (segment 8, MAPSYM_SITE_NAME) */

int far QueenMoveR(int x, int y, int dirHint)
{
    int dir;
    int newRow;
    int newCol;
    int opp;
    int index;

    dir = GetBestDir(3, x, y, TileMassXR, TileMassYR);
    if (dir < 0) {
        dir++;
        if (dir == 0)
            return 0;
        dir = SRand8();
    }
    if (y < 3) {
        if (dir > 5)
            return 0;
        if (dir < 3)
            return 0;
    }
    if (TryMoveDirR(x, y, dir) != 0) {
                opp = (dirHint ^ 0xfc) & 7;
                newCol = x + Dx8[opp];
                newRow = y + Dy8[opp + 8];
                LifeR[newCol * 64 + newRow] = 0;

                index = FindInRList(newCol, newRow, (dirHint & 7) + 0xe8);
                if (index >= 0 && RlistX.t[index] != 0) {
                    RlistX.x[index] = (char)x;
                    RlistX.y[index] = (char)y;
                    RlistX.t[index] = (char)(dir - 0x18);
                    LifeR[x * 64 + y] = (unsigned char)(dir - 0x18);
                }
        return 1;
    }
    return 0;
}
