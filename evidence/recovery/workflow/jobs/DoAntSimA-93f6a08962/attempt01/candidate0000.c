/*
 * DoAntSimA: outer per-tick simulation loop over the A-list (yellow/food
 * ant) records.  Tindex counts down from ListIndexA to 0; for each
 * record a SRand256()==0 random death check against HealthB/HealthR
 * (selected by the record's own colour bit, AlistT&0x80) can kill the
 * ant via DeadAntHere and bump BAntsExpired.  A zero AlistT record is
 * skipped.  Otherwise the record's AlistM mode (0..19) is used to bump
 * TemBModePop/TemRModePop (by colour) and dispatch inline to one of the
 * per-mode workers (DoRandAntA, DoToNestAnt, DoForageAnt,
 * DoReturnFoodAnt, DoDigOutAntA, DoRecruitAnt, DoAttackAnt, DoFightA,
 * DoToAlarm, DoRepoExit) or to inline egg-expire, smell/trail-avoidance,
 * pheromone-following, nest-entry, and swarm/queen-storage-absorption
 * logic matching this codebase's other DoAntSim*-family dispatchers.
 * modes 1 and 4 share DoToNestAnt as their single-argument worker; modes
 * 17 and 18 (and anything past 19) fall through with no action.
 */
extern unsigned char near LifeA[];
extern unsigned char near MapA[];
extern int near HealthB;
extern int near HealthR;
extern int near QueenStorageB;
extern int near QueenStorageR;
extern int near CurGameType;
extern int far Tindex;
extern int far ListIndexA;
extern unsigned char far Dx8[];
extern signed char far Dy8[];
extern unsigned char far PherMapBN[];
extern unsigned char far PherMapRN[];
extern int far TemBModePop[];
extern int far TemRModePop[];
extern long far BAntsExpired;
extern int far FlyAwayB;
extern int far FlyAwayR;
extern int far SwarmCntB;
extern int far SwarmCntR;
extern int far TERRAINset;

extern int far SRand256(void);
extern int far SRand32(void);
extern int far SRand16(void);
extern int far SRand4(void);
extern int far SRand2(void);
extern int far SRand1(int range);
extern int far IsValidA(int x, int y);
extern int far FindInAList(int x, int y);
extern void far DeadAntHere(int colour, int y, int x);
extern void far InvalQueenStorageDisp(void);
extern void far RestBalloons(int plane, int x, int y);
extern void far GoInNest(int x, int y, int index);

extern void far DoRandAntA(int index);
extern void far DoRandAntAA(int index);
extern void far DoToNestAnt(int index);
extern void far DoForageAnt(int index);
extern void far DoReturnFoodAnt(int index);
extern void far DoDigOutAntA(int index);
extern void far DoRecruitAnt(int index);
extern void far DoAttackAnt(int index);
extern void far DoFightA(int index);
extern void far DoToAlarm(int index);
extern void far DoRepoExit(int index);
extern void far DoRepoLoit(int index);

#define AlistM(i) Dx8[(i) + 0x2b78]
#define AlistT(i) Dx8[(i) + 0x2f62]
#define AlistX(i) Dx8[(i) + 0x23a4]
#define AlistY(i) Dx8[(i) + 0x278e]

void far DoAntSimA(void)
{
    int attr;
    int mode;
    int x;
    int y;
    int nx;
    int ny;
    int canMove;

    Tindex = ListIndexA;
    if (Tindex <= 0)
        return;

    do {
        Tindex--;

        if (SRand256() == 0 && AlistT(Tindex) != 0) {
            int health = (AlistT(Tindex) & 0x80) ? HealthR : HealthB;
            if (SRand32() > health) {
                DeadAntHere(AlistT(Tindex) & 0x80, AlistY(Tindex), AlistX(Tindex));
                AlistT(Tindex) = 0;
                BAntsExpired++;
            }
        }

        attr = AlistT(Tindex);
        if (attr == 0)
            continue;

        mode = AlistM(Tindex);
        if (attr & 0x80)
            TemRModePop[mode]++;
        else
            TemBModePop[mode]++;

        if (mode > 0x13)
            continue;

        switch (mode) {
        case 0:
            DoRandAntA(Tindex);
            break;

        case 1:
        case 4:
            DoToNestAnt(Tindex);
            break;

        case 2:
            DoForageAnt(Tindex);
            break;

        case 3:
            DoReturnFoodAnt(Tindex);
            break;

        case 5:
            DoDigOutAntA(Tindex);
            break;

        case 6:
            DoRecruitAnt(Tindex);
            break;

        case 7:
            DoAttackAnt(Tindex);
            break;

        case 8:
            x = AlistX(Tindex);
            y = AlistY(Tindex);
            LifeA[(x << 6) + y] = attr;
            if (SRand1(200) == 0) {
                AlistT(Tindex) = 0;
                LifeA[(x << 6) + y] = 0;
            }
            break;

        case 9:
            x = AlistX(Tindex);
            y = AlistY(Tindex);
            LifeA[(x << 6) + y] = attr;
            if ((attr & 0x7f) <= 0x67)
                break;
            ny = y + Dy8[attr & 7];
            nx = x + Dx8[attr & 7];
            canMove = (LifeA[(nx << 6) + ny] - attr == -8) ? 0 : (FindInAList(nx, ny) < 0);
            if (!canMove)
                break;
            LifeA[(x << 6) + y] = 0;
            AlistT(Tindex) = 0;
            break;

        case 10:
            DoFightA(Tindex);
            break;

        case 11:
            DoToAlarm(Tindex);
            break;

        case 12:
            x = AlistX(Tindex);
            y = AlistY(Tindex);
            if (attr & 0x80) {
                if (PherMapRN[((x & 0xfe) << 4) + (y >> 1)] >= 0x6e)
                    DoRandAntAA(Tindex);
                else
                    DoToNestAnt(Tindex);
            } else {
                if (PherMapBN[((x & 0xfe) << 4) + (y >> 1)] >= 0x6e)
                    DoRandAntAA(Tindex);
                else
                    DoToNestAnt(Tindex);
            }
            break;

        case 13:
            x = AlistX(Tindex);
            y = AlistY(Tindex);
            if (IsValidA(x, y)) {
                if (TERRAINset == 0) {
                    if (MapA[(x << 6) + y] == 0x50)
                        canMove = 1;
                    else
                        canMove = 0;
                } else {
                    int t = MapA[(x << 6) + y];
                    canMove = (t >= 0x80 && t <= 0x8f) ? 1 : 0;
                }
            } else {
                canMove = 0;
            }
            if (canMove) {
                GoInNest(x, y, Tindex);
                break;
            }
            if (SRand4() == 0) {
                AlistM(Tindex) = 2;
                break;
            }
            if (TERRAINset == 1)
                RestBalloons(1, x, y);
            break;

        case 14:
            if (SRand2() == 0)
                DoRandAntAA(Tindex);
            else
                DoToNestAnt(Tindex);
            if (AlistT(Tindex) & 0x80) {
                if (FlyAwayR > 100)
                    AlistM(Tindex) = 0xf;
            } else {
                if (FlyAwayB > 100)
                    AlistM(Tindex) = 0xf;
            }
            break;

        case 15:
            DoRepoExit(Tindex);
            break;

        case 16:
            if (SRand32() != 0)
                break;
            if ((attr & 0x80) == 0 && SwarmCntB >= 0x32)
                break;
            if ((attr & 0x80) != 0 && SwarmCntR >= 0x32)
                break;
            x = AlistX(Tindex);
            y = AlistY(Tindex);
            AlistT(Tindex) = 0;
            LifeA[(x << 6) + y] = 0;
            if (CurGameType != 2)
                break;
            if (attr & 0x80)
                SwarmCntR++;
            else
                SwarmCntB++;
            if (SRand16() != 0)
                break;
            if (attr & 0x80) {
                QueenStorageR++;
            } else {
                QueenStorageB++;
                InvalQueenStorageDisp();
            }
            break;

        case 17:
        case 18:
            break;

        case 19:
            DoRepoLoit(Tindex);
            break;
        }
    } while (Tindex > 0);
}
