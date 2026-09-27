/*
 * MoveSpider advances the spider clock, handles the player-controlled
 * pursuit state, scans the surrounding ant cells, and dispatches the six
 * spider movement states.  The final paths update ant, corpse, food, sound,
 * and terrain state.
 */
extern int far Scycle2;
extern int far Scycle;
extern int far SMode[];
extern int far MeMode;
extern int far MeSMode;
extern int far SpidOn;
extern int far SpidRevenge;
extern int far RevSpider;
extern int far CurGameType;
extern int far Starg;
extern int far StargLife;
extern int far SuserX;
extern int far SuserY;
extern int far SpidBurpCnt;
extern int far EatCnt;
extern int far SCorpseBase;
extern int far DeathCnt[];
extern int far OptionStates[];
extern int far TERRAINset[];
extern long far RAntsEaten;
extern long far BAntsEaten;
extern unsigned char far AlistT[];
extern unsigned char far AlistX[];
extern unsigned char far AlistY[];
extern unsigned char far TurnTab[];
extern signed char far SpX[];
extern signed char far SpY[];
extern signed char far SeatX[];
extern signed char far SeatY[];
extern int near SpidX;
extern int near SpidY;
extern int near SpidDir;
extern int near MeLocX;
extern int near MeLocY;
extern int near MePlane;
extern int near MeType;
extern int near MeDir;
extern unsigned char near LifeA[];
extern unsigned char near MapA[];
extern int __based(__segname("PACK")) MeCmd;
extern int far SFoundAnt(void);
extern int far SpiderScan(void);
extern int far GetDis(int x1, int y1, int x2, int y2);
extern int far GetBestDir(int x1, int y1, int x2, int y2, int mode);
extern int far GetDir(int x1, int y1, int x2, int y2);
extern int far SRand1(int range);
extern int far SRand2(void);
extern int far SRand4(void);
extern int far SRand256(void);
extern void far GotoMyAnt(void);
extern void far DropFoodA(int x, int y);
extern void far YellowDeath(int reason);
extern void far PictStrnDialog(int picture, int object, int force);
extern void far myBeginSound(unsigned int effect, unsigned int mode,
                             unsigned int repeats);
extern void far MoveMyLife(int plane, int x, int y, int type,
                           int direction);
extern void far DeadAntHere(int x, int y, int colour);
extern int far IsValidA(int x, int y);

void far MoveSpider(void)
{
    register int x;
    register int y;
    int target;
    int direction;
    int distance;
    int nearby;
    int dx;
    int dy;
    int row;
    int column;
    int cellX;
    int cellY;
    int targetX;
    int targetY;
    int targetLife;
    int random;
    int newX;
    int newY;
    int mapIndex;
    int far *meMode;
    int far *spiderMode;
    int far *spiderOn;
    int far *targetAnt;
    int far *targetLifePtr;
    int far *revenge;
    int far *deathCount;

    /* The animation clock wraps at ten bits; retain the current tile. */
    Scycle2 = (Scycle2 + 1) & 0x3ff;
    x = SpidX >> 4;
    y = SpidY >> 4;
    meMode = &MeMode;
    spiderMode = &SMode[0];

    /* A live player ant selects either an acquired target or a user chase. */
    if (*meMode == 1) {
        if (*spiderMode == 2 || *spiderMode == 3)
            goto spider_state;

        if (MeSMode == 7) {
            target = SFoundAnt();
            targetAnt = &Starg;
            *targetAnt = target;
            targetLifePtr = &StargLife;
            if (target == -2) {
                *targetLifePtr = -1;
                return;
            }
            *spiderMode = 2;
            if (target >= 0)
                *targetLifePtr = AlistT[target];
            else
                *targetLifePtr = -1;
            return;
        }

        if (MeSMode == 8) {
            SpiderScan();
            distance = GetDis(MeLocX, MeLocY, SuserX, SuserY);
            if (distance < 1) {
                Scycle = 2;
                return;
            }

            direction = GetBestDir(1, SuserX, SuserY,
                                   MeLocX, MeLocY, 1);
            if (direction == -1)
                return;
            if (direction == -2) {
                direction = GetDir(SuserX, SuserY,
                                   MeLocX, MeLocY) - 1;
                if (direction < 0)
                    return;
            }

            if (direction >= 0 && direction < 8) {
                SpidDir = TurnTab[SpidDir * 8 + direction];
                if (MeCmd != 0 && distance > 2) {
                    SpidX += SpX[SpidDir] * 5;
                    SpidY += SpY[SpidDir] * 5;
                    Scycle = (Scycle + 2) & 0x3ff;
                } else {
                    SpidX += SpX[SpidDir];
                    SpidY += SpY[SpidDir];
                    Scycle = (Scycle + 1) & 0x3ff;
                }
            }

            MeLocX = SpidX >> 4;
            MeLocY = SpidY >> 4;
            if (OptionStates[0] != 0)
                GotoMyAnt();
            return;
        }
    }

    /* An inactive spider may appear only in the ordinary game type. */
spider_state:
    spiderOn = &SpidOn;
    spiderMode = &SMode[0];
    if (*spiderOn != 0)
        goto movement_gate;
    if (CurGameType != 0 || SRand1(300) != 0)
        return;

    SpidX = SRand1(0x400) + 0x200;
    SpidY = 0x200;
    *spiderOn = 1;
    *spiderMode = 1;
    RevSpider = 0;
    if (SRand1(2) == 0) {
        SpidY = 1;
        SpidDir = 4;
    } else {
        SpidY = 0x3ff;
        SpidDir = 0;
    }
    return;

    /* Ant pressure is counted over the 128-by-64 LifeA grid. */
movement_gate:
    spiderMode = &SMode[0];
    spiderOn = &SpidOn;
    if ((Scycle2 & 3) != 0 || *spiderMode >= 5)
        goto before_dispatch;

    x = SpidX >> 4;
    y = SpidY >> 4;
    nearby = 0;
    for (row = -1; row <= 1; ++row) {
        for (column = -1; column <= 1; ++column) {
            cellX = x + row;
            cellY = y + column;
            if (cellX >= 0 && cellX <= 127 &&
                cellY >= 0 && cellY <= 63 &&
                LifeA[cellX * 64 + cellY] != 0)
                ++nearby;
        }
    }

    if (nearby > 8) {
        *spiderMode = 5;
        DeathCnt[0] = 500;
        Scycle = 0;
        if (*meMode != 1) {
            PictStrnDialog(0, 0x273e, 0);
            revenge = &SpidRevenge;
            if (*revenge < 5)
                ++*revenge;
            if (*revenge < 3)
                return;
            if (*revenge >= 5)
                MeSMode = 8;
            else
                MeSMode = 7;
            if (*revenge >= 6 && SRand2() == 0) {
                *revenge = 0;
                MeSMode = 0;
            }
            return;
        }
        *meMode = 0;
        YellowDeath(3);
        return;
    }

    if (nearby > 4)
        *spiderMode = 4;

    /* A user-directed scan is refreshed before the state jump table. */
before_dispatch:
    if (*spiderMode < 4 && MeSMode == 8)
        SpiderScan();
    if (*spiderMode > 5)
        return;

    switch (*spiderMode) {
    case 0:
        Scycle = 2;
        if (SRand1(150) == 0) {
            *spiderMode = 1;
            target = SFoundAnt();
            targetAnt = &Starg;
            *targetAnt = target;
            if (target != -2) {
                *spiderMode = 2;
                targetLifePtr = &StargLife;
                if (target >= 0)
                    *targetLifePtr = AlistT[target];
                else
                    *targetLifePtr = -1;
                return;
            }
        }
        if (SRand1(30) == 0) {
            random = SRand1(8);
            SpidDir = TurnTab[SpidDir * 8 + random];
        }
        if (MeSMode == 8)
            SpiderScan();
        goto validate_location;

    case 1:
        direction = SpidDir & 7;
        if (RevSpider) {
            SpidX -= SpX[direction];
            SpidY -= SpY[direction];
            --Scycle;
        } else {
            SpidX += SpX[direction];
            SpidY += SpY[direction];
            Scycle = (Scycle + 1) & 0x3ff;
        }
        if (SRand1(20) == 0) {
            random = SRand1(8);
            SpidDir = TurnTab[SpidDir * 8 + random];
        }
        target = SFoundAnt();
        targetAnt = &Starg;
        *targetAnt = target;
        if (target != -2) {
            *spiderMode = 2;
            targetLifePtr = &StargLife;
            if (target >= 0)
                *targetLifePtr = AlistT[target];
            else
                *targetLifePtr = -1;
            return;
        }
        if (SRand1(50) == 0) {
            *spiderMode = 0;
            Scycle = 2;
        }
        goto validate_location;

    case 2:
        targetAnt = &Starg;
        targetLifePtr = &StargLife;
        target = *targetAnt;
        if (target >= 0) {
            targetLife = *targetLifePtr;
            if (((AlistT[target] ^ targetLife) & 0xf0) != 0) {
                *spiderMode = 0;
                *targetAnt = -2;
                if (*meMode == 1) {
                    SuserX = SpidX >> 4;
                    SuserY = SpidY >> 4;
                    if (MeSMode == 6)
                        MeSMode = 0;
                    if (OptionStates[0] != 0)
                        GotoMyAnt();
                }
                return;
            }
            targetX = AlistX[target] & 0xff;
            targetY = AlistY[target];
        } else {
            if (MePlane > 1) {
                *spiderMode = 0;
                *targetAnt = -2;
                return;
            }
            targetX = MeLocX;
            targetY = MeLocY;
        }

        dx = targetX - x;
        dy = targetY - y;
        if (dx < 0)
            dx = -dx;
        if (dy < 0)
            dy = -dy;
        distance = dx + dy;
        if (distance > 0x40 && *meMode != 1) {
            *spiderMode = 0;
            *targetAnt = -2;
            return;
        }
        if (distance < 2) {
            *spiderMode = 3;
            SpidX = (SpidX & 0xfff0) + 8;
            SpidY = (SpidY & 0xfff0) + 8;
            goto ant_contact;
        }

        direction = GetDir(x, y, targetX, targetY);
        SpidDir = TurnTab[SpidDir * 8 + direction];
        myBeginSound(0x2f, 0, target < 0 ? 0x7e : -5);
        if (RevSpider) {
            SpidX -= SpX[SpidDir] * 2;
            SpidY -= SpY[SpidDir] * 2;
            Scycle -= 2;
        } else {
            SpidX += SpX[SpidDir] * 2;
            SpidY += SpY[SpidDir] * 2;
            Scycle = (Scycle + 2) & 0x3ff;
        }
        MeLocX = SpidX >> 4;
        MeLocY = SpidY >> 4;
        if (OptionStates[0] != 0)
            GotoMyAnt();
        goto validate_location;

    case 3:
ant_contact:
        if (*meMode == 1) {
            MeLocX = SpidX >> 4;
            MeLocY = SpidY >> 4;
            if (MeSMode == 6) {
                MeSMode = 0;
                GotoMyAnt();
            }
        }
        if (OptionStates[0] != 0)
            GotoMyAnt();

        targetAnt = &Starg;
        targetLifePtr = &StargLife;
        target = *targetAnt;
        if (target == -2)
            goto feed_and_clean;
        if (target < 0)
            goto player_ant_contact;

        targetLife = *targetLifePtr;
        if (((AlistT[target] ^ targetLife) & 0xf0) != 0) {
            *spiderMode = 0;
            *targetAnt = -2;
            goto spider_cleanup;
        }
        if (targetLife & 0x80) {
            ++RAntsEaten;
            SCorpseBase = 4;
        } else {
            ++BAntsEaten;
            SCorpseBase = 0;
        }
        targetX = AlistX[target] & 0xff;
        targetY = AlistY[target];
        LifeA[targetX * 64 + targetY] = 0;
        AlistT[target] = 0;
        *targetAnt = -2;
        goto spider_cleanup;

    case 4:
        random = SRand1(8);
        SpidDir = TurnTab[SpidDir * 8 + random];
        direction = SpidDir;
        if (RevSpider) {
            SpidX -= SpX[direction] * 5;
            SpidY -= SpY[direction] * 5;
            Scycle -= 2;
        } else {
            SpidX += SpX[direction] * 5;
            SpidY += SpY[direction] * 5;
            Scycle = (Scycle + 2) & 0x3ff;
        }
        if (SRand1(50) == 0) {
            *spiderMode = 0;
            Scycle = 2;
        }
        goto validate_location;

    case 5:
        deathCount = &DeathCnt[0];
        --*deathCount;
        if (*deathCount == 0) {
            *spiderOn = 0;
            *spiderMode = 0;
            DropFoodA(x, y);
            DropFoodA(x, y);
            DropFoodA(x, y);
            return;
        }
        random = SRand1(1000);
        if (random < *deathCount) {
            if (*deathCount > 0x190)
                *spiderMode = SRand1(3) + 1;
            else
                Scycle = SRand1(2) + 2;
        }
        goto validate_location;
    }
    return;

player_ant_contact:
    newX = (x + SeatX[SpidDir]) & 0x7f;
    newY = (y + SeatY[SpidDir]) & 0x3f;
    MoveMyLife(MePlane, newX, newY, MeType, MeDir);
    YellowDeath(1);
    SCorpseBase = 0;
    *targetAnt = -2;

    /* Update the map, feeding timer, burp timer, and corpse callback. */
feed_and_clean:
    if (MeSMode >= 7)
        EatCnt = 11;
    else
        EatCnt = 50;

    newX = (x + SeatX[SpidDir]) & 0x7f;
    newY = (y + SeatY[SpidDir]) & 0x3f;
    if (TERRAINset[0] != 0) {
        mapIndex = newX * 64 + newY;
        if (MapA[mapIndex] < 0x18)
            MapA[mapIndex] = SRand4() + SCorpseBase + 0x10;
    }

    if (EatCnt > 0) {
        --EatCnt;
        if (EatCnt % 10 == 0 && SRand2() == 0)
            myBeginSound(0x2c, (SRand256() << 3) + 0x2777, -5);
    }

    --SpidBurpCnt;
    if (SpidBurpCnt == 0) {
        SpidBurpCnt = 10;
        if (OptionStates[5] != 0 && SRand2() == 0)
            myBeginSound(10, 0, 10);
    }
    DeadAntHere(newY, newX, SCorpseBase);

    /* Clear the completed chase, update the user target, then validate. */
spider_cleanup:
    *spiderMode = 0;
    if (MeSMode == 6)
        MeSMode = 0;
    SuserX = SpidX >> 4;
    SuserY = SpidY >> 4;

    /* Losing the player tile can kill the player's current ant. */
validate_location:
    if (IsValidA(SpidX >> 4, SpidY >> 4) == 0) {
        *spiderOn = 0;
        if (*meMode == 1) {
            *meMode = 0;
            YellowDeath(4);
        }
    }
    if (TERRAINset[0] != 0) {
        mapIndex = ((SpidX & 0xfff0) << 2) + (SpidY >> 4);
        if (MapA[mapIndex] > 0x90)
            *spiderMode = 0;
    }
}
