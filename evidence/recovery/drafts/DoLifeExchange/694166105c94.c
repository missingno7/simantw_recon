/*
 * DoLifeExchange has two entry routes and one shared takeover tail.  An empty
 * surface cell starts life-transfer mode after saving the current ant in its
 * plane's list.  An occupied cell is resolved back to its list entry by the
 * three coordinate/type arrays; a queen also has a separate rear-cell entry.
 * Normal exchange removes the selected ant, records the current ant at its
 * former location, and then installs the selected ant in the player's state.
 * While transfer mode is active, the selected ant is removed and installed
 * without reinserting the hidden player ant.
 */
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern int near MeColor;
extern int near MeDir;
extern int near MeEgg;
extern int near MeFoodInType;
extern int near MeHealth;
extern int near MeLocX;
extern int near MeLocY;
extern int near MePlane;
extern int near MeType;
extern int near SpidX;
extern int near SpidY;
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistT[];
extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
extern int far MeMode;
extern int far MeEggCarried;
extern unsigned char far UnCarryCaste[];
extern int far Starg;
extern int far SuserX;
extern int far SuserY;
extern int far SMode;
extern int far MeSMode;
extern int far MeHealthCntDwn;
extern int far MeWarnHealth;
extern int far MeWantFood;
extern long near GetDis(int x1, int y1, int x2, int y2);
extern void near AddAntToAList(int life, int column, int state,
                              int attribute, int direction);
extern void near AddAntToBList(int life, int column, int state,
                              int attribute, int direction);
extern void near AddAntToRList(int life, int column, int state,
                              int attribute, int direction);
extern int near GetAntIndex(int list, int index, int far *life,
                           int far *column, int far *attribute,
                           int far *state, int far *direction);
extern void near SetAntIndex(int list, int index, int life, int column,
                            int attribute, int state, int direction);
extern void near SetLife(int plane, int x, int y, int value);
extern void far ResetYellowVars(int plane, int x, int y);
extern void far ZapEuMapAt(int plane, int x, int y);

int far DoLifeExchange(int plane, int x, int y)
{
    int result;
    int inBounds;
    int life;
    int kind;
    int index;
    int tailIndex;
    int count;
    int i;
    unsigned long distance;
    int selectedPlane;
    int selectedLife;
    int currentPlane;
    int currentX;
    int currentY;
    int currentType;
    int currentKind;
    int currentLife;
    int currentAttribute;
    int clearPlane;
    int clearX;
    int clearY;
    int clearType;
    int clearDirection;
    int tailX;
    int tailY;
    int tailLife;
    int antLife;
    int antColumn;
    int antAttribute;
    int antState;
    int antDirection;
    unsigned char __based(__segname("SIMANT_DATA_GROUP")) *scanX;
    unsigned char __based(__segname("SIMANT_DATA_GROUP")) *scanY;
    unsigned char __based(__segname("SIMANT_DATA_GROUP")) *scanType;

    /* Entry bounds and the three near Life planes. */
    life = -1;
    inBounds = -1;
    if (plane <= 1) {
        if (x >= 0 && x <= 0x7f && y >= -1 && y <= 0x3f)
            inBounds = 1;
    } else if (x >= 0 && x <= 0x3f &&
               y >= -1 && y <= 0x3f) {
        inBounds = 1;
    }
    if (--inBounds == 0) {
        switch (plane) {
        case 0:
        case 1:
            life = LifeA[x][y];
            break;
        case 2:
            life = LifeB[x][y];
            break;
        case 3:
            life = LifeR[x][y];
            break;
        }
    }

    /* Empty surface selection: add the held ant, then enter transfer mode. */
    if (life <= 0) {
        if (plane != 1)
            return 0;
        distance = GetDis((x << 4) + 8, (y << 4) + 8,
                               SpidX, SpidY);
        if (distance >= 0x200)
            return 0;
        if (MeMode == 1)
            return 1;

        currentType = MeType;
        kind = (currentType & 0x78) >> 3;
        if (currentType & 8) {
            if (kind == 5 || kind == 9)
                kind = UnCarryCaste[kind];
            else if (kind == 1)
                kind = MeEggCarried;
        }
        currentLife = (kind << 3) | (MeColor & 0x80) | MeDir;
        currentAttribute = 0;
        if (currentType == 0x60)
            currentAttribute = 9;
        currentX = MeLocX;
        currentY = MeLocY;
        currentPlane = MePlane;

        result = 0;
        if (currentPlane <= 1) {
            if (ListIndexA < 1000) {
                AddAntToAList(currentX, currentY, currentLife,
                              currentAttribute, 0);
                result = 1;
            }
        } else if (currentPlane == 2) {
            if (ListIndexB < 500) {
                AddAntToBList(currentX, currentY, currentLife,
                              currentAttribute, 0);
                result = 1;
            }
        } else if (ListIndexR < 500) {
            AddAntToRList(currentX, currentY, currentLife,
                          currentAttribute, 0);
            result = 1;
        }
        if (result != 1)
            return 0;
        SetLife(currentPlane, currentX, currentY, currentLife);

        if (currentType == 0x60) {
            tailX = currentX + Dx8[MeDir ^ 4];
            tailY = currentY + Dy8[MeDir ^ 4];
            result = 0;
            if (currentPlane <= 1) {
                if (ListIndexA < 1000) {
                    AddAntToAList(tailX, tailY, currentLife + 8,
                                  currentAttribute, 0);
                    result = 1;
                }
            } else if (currentPlane == 2) {
                if (ListIndexB < 500) {
                    AddAntToBList(tailX, tailY, currentLife + 8,
                                  currentAttribute, 0);
                    result = 1;
                }
            } else if (ListIndexR < 500) {
                AddAntToRList(tailX, tailY, currentLife + 8,
                              currentAttribute, 0);
                result = 1;
            }
            if (result != 1)
                return 0;
            SetLife(currentPlane, tailX, tailY, currentLife + 8);
        }

        /* Reload the player's current state and clear the old map cells only
           when their coordinates are valid for this plane. */
        clearPlane = MePlane;
        clearX = MeLocX;
        clearY = MeLocY;
        clearType = MeType;
        clearDirection = MeDir;
        inBounds = 0;
        if (clearPlane <= 1) {
            if (clearX >= 0 && clearX <= 0x7f &&
                clearY >= 0 && clearY <= 0x3f)
                inBounds = 1;
        } else if (clearX >= 0 && clearX <= 0x3f &&
                   clearY >= 0 && clearY <= 0x3f) {
            inBounds = 1;
        }
        if (inBounds) {
            SetLife(clearPlane, clearX, clearY, 0);
            if (clearType == 0x60)
                SetLife(clearPlane,
                        clearX + Dx8[clearDirection ^ 4],
                        clearY + Dy8[clearDirection ^ 4], 0);
        }

        Starg = -2;
        SuserX = SpidX >> 4;
        SuserY = SpidY >> 4;
        MeMode = 1;
        SMode = 0;
        MeSMode = 0;
        MeColor = 0;
        ResetYellowVars(plane, SpidX >> 4, SpidY >> 4);
        MeHealth = 100;
        MeHealthCntDwn = 0;
        if (MeWarnHealth >= MeHealth || MeHealth < 10)
            MeWantFood = 1;
        else
            MeWantFood = 0;
        return 1;
    }

    /* A list entry is selected.  Ignore a queen body/rear cell that is not
       a selectable ant, and preserve the transfer-mode distance gate. */
    selectedLife = life;
    selectedPlane = plane;
    if (selectedPlane == 0)
        selectedPlane = 1;
    if (MePlane == selectedPlane) {
        if (MeMode == 1) {
            if (plane <= 1) {
                distance = GetDis((x << 4) + 8, (y << 4) + 8,
                                  SpidX, SpidY);
                if (distance < 0x200)
                    return 1;
            }
        } else {
            if (plane <= 1)
                selectedLife = LifeA[x][y];
            else if (plane == 2)
                selectedLife = LifeB[x][y];
            else
                selectedLife = LifeR[x][y];
        }
    }
    if (selectedLife == 0xff || selectedLife == 0xfe)
        return 1;

    /* Normalize a selected queen cell to its body record.  Selecting the
       queen's rear cell requires reading the adjacent body cell first. */
    kind = (selectedLife & 0x78) >> 3;
    tailIndex = -1;
    if (kind == 12) {
        tailX = x + Dx8[(selectedLife ^ 0xfc) & 7];
        tailY = y + Dy8[(selectedLife ^ 0xfc) & 7];
        if (plane <= 1) {
            if (tailX >= 0 && tailX <= 0x7f &&
                tailY >= 0 && tailY <= 0x3f)
                tailLife = LifeA[tailX][tailY];
            else
                tailLife = -1;
        } else if (plane == 2) {
            if (tailX >= 0 && tailX <= 0x3f &&
                tailY >= 0 && tailY <= 0x3f)
                tailLife = LifeB[tailX][tailY];
            else
                tailLife = -1;
        } else {
            if (tailX >= 0 && tailX <= 0x3f &&
                tailY >= 0 && tailY <= 0x3f)
                tailLife = LifeR[tailX][tailY];
            else
                tailLife = -1;
        }
        if (tailLife == 0)
            tailLife = -1;
    } else if (kind == 13) {
        tailX = x;
        tailY = y;
        tailLife = selectedLife;
        x += Dx8[selectedLife & 7];
        y += Dy8[selectedLife & 7];
        life = -1;
        if (plane <= 1) {
            if (x < 0 || x > 0x7f || y < 0 || y > 0x3f)
                goto body_life_ready;
        } else if (plane == 2) {
            if (x < 0 || x > 0x3f || y < 0 || y > 0x3f)
                goto body_life_ready;
        } else if (plane == 3) {
            if (x < 0 || x > 0x3f || y < 0 || y > 0x3f)
                goto body_life_ready;
        }
        switch (plane) {
        case 0:
        case 1:
            life = LifeA[x][y];
            break;
        case 2:
            life = LifeB[x][y];
            break;
        case 3:
            life = LifeR[x][y];
            break;
        }
body_life_ready:
        if (life == 0)
            life = -1;
        selectedLife = life;
        kind = 12;
    }

    /* Resolve the body cell to its live record, walking the selected plane's
       parallel coordinate/type arrays from newest to oldest. */
    if (plane <= 1) {
        count = ListIndexA;
        scanX = AlistX;
        scanY = AlistY;
        scanType = AlistT;
    } else if (plane == 2) {
        count = ListIndexB;
        scanX = BlistX;
        scanY = BlistY;
        scanType = BlistT;
    } else {
        count = ListIndexR;
        scanX = RlistX;
        scanY = RlistY;
        scanType = RlistT;
    }
    index = -1;
    for (i = count - 1; i >= 0; --i) {
        if (scanX[i] == x && scanY[i] == y && scanType[i] == selectedLife) {
            index = i;
            break;
        }
    }
    if (index < 0)
        return 0;

    /* Only the queen body has a second live tuple.  Kind 13 was normalized
       above and now uses this same body/tail pair. */
    if (kind == 12) {
        if (plane <= 1) {
            count = ListIndexA;
            scanX = AlistX;
            scanY = AlistY;
            scanType = AlistT;
        } else if (plane == 2) {
            count = ListIndexB;
            scanX = BlistX;
            scanY = BlistY;
            scanType = BlistT;
        } else {
            count = ListIndexR;
            scanX = RlistX;
            scanY = RlistY;
            scanType = RlistT;
        }
        tailIndex = -1;
        for (i = count - 1; i >= 0; --i) {
            if (scanX[i] == tailX && scanY[i] == tailY &&
                scanType[i] == tailLife) {
                tailIndex = i;
                break;
            }
        }
    }

    /* The ordinary swap path saves list outputs, clears the selected body,
       and inserts the old player ant.  Active transfer skips that insertion. */
    if (MeMode == 0) {
        currentPlane = MePlane;
        currentX = MeLocX;
        currentY = MeLocY;
        currentType = MeType;
        currentKind = (currentType & 0x78) >> 3;
        if (currentType & 8) {
            if (currentKind == 5 || currentKind == 9)
                currentKind = UnCarryCaste[currentKind];
            else if (currentKind == 1)
                currentKind = MeEggCarried;
        }
        currentLife = (currentKind << 3) |
                      (selectedLife & 0x80) | MeDir;
        if (selectedLife & 0x80)
            return 0;
        currentAttribute = 0;
        if (currentType == 0x60)
            currentAttribute = 9;

        if (kind <= 0 || kind > 13 || kind == 10 || kind == 11)
            return 0;
        if (kind == 1) {
            GetAntIndex(plane, index, &antLife, &antColumn,
                        &antAttribute, &antState, &antDirection);
            MeEggCarried = antDirection;
        } else if (kind == 5 || kind == 9) {
            selectedLife = (UnCarryCaste[kind] << 3) |
                           (selectedLife & 7);
        }

        ZapEuMapAt(currentPlane, currentX, currentY);
        if (currentType == 0x60)
            ZapEuMapAt(currentPlane, currentX + Dx8[MeDir ^ 4],
                       currentY + Dy8[MeDir ^ 4]);
        ZapEuMapAt(plane, x, y);
        if (kind == 12)
            ZapEuMapAt(plane, tailX, tailY);
        SetAntIndex(plane, index, 0, 0, 0, 0, 0);
        if (kind == 12)
            SetAntIndex(plane, tailIndex, 0, 0, 0, 0, 0);

        result = 0;
        if (currentPlane <= 1) {
            if (ListIndexA < 1000) {
                AddAntToAList(currentX, currentY, currentLife,
                              currentAttribute, 0);
                result = 1;
            }
        } else if (currentPlane == 2) {
            if (ListIndexB < 500) {
                AddAntToBList(currentX, currentY, currentLife,
                              currentAttribute, 0);
                result = 1;
            }
        } else if (ListIndexR < 500) {
            AddAntToRList(currentX, currentY, currentLife,
                          currentAttribute, 0);
            result = 1;
        }
        if (result != 1)
            return 0;
        SetLife(currentPlane, currentX, currentY, currentLife);
        if (currentType == 0x60) {
            tailX = currentX + Dx8[MeDir ^ 4];
            tailY = currentY + Dy8[MeDir ^ 4];
            result = 0;
            if (currentPlane <= 1) {
                if (ListIndexA < 1000) {
                    AddAntToAList(tailX, tailY, currentLife + 8,
                                  currentAttribute, 0);
                    result = 1;
                }
            } else if (currentPlane == 2) {
                if (ListIndexB < 500) {
                    AddAntToBList(tailX, tailY, currentLife + 8,
                                  currentAttribute, 0);
                    result = 1;
                }
            } else if (ListIndexR < 500) {
                AddAntToRList(tailX, tailY, currentLife + 8,
                              currentAttribute, 0);
                result = 1;
            }
            if (result != 1)
                return 0;
            SetLife(currentPlane, tailX, tailY, currentLife + 8);
        }
    } else {
        if (selectedLife & 0x80)
            return 0;
        kind = (selectedLife & 0x78) >> 3;
        if (kind <= 0 || kind > 13 || kind == 10 || kind == 11)
            return 0;
        if (kind == 1) {
            GetAntIndex(plane, index, &antLife, &antColumn,
                        &antAttribute, &antState, &antDirection);
            MeEggCarried = antDirection;
        } else if (kind == 5 || kind == 9) {
            selectedLife = (UnCarryCaste[kind] << 3) |
                           (selectedLife & 7);
        }
        SetAntIndex(plane, index, 0, 0, 0, 0, 0);
        if (kind == 12)
            SetAntIndex(plane, tailIndex, 0, 0, 0, 0, 0);
    }

    /* Install the selected ant, rebuild its queen rear cell when needed, and
       reset the health/tool state shared by both takeover routes. */
    MeColor = selectedLife & 0x80;
    MeFoodInType = 0;
    MeMode = 0;
    MeSMode = 0;
    MeHealth = 100;
    MeHealthCntDwn = 0;
    if (MeHealth <= MeWarnHealth || MeHealth < 10)
        MeWantFood = 1;
    else
        MeWantFood = 0;

    inBounds = 0;
    if (plane <= 1) {
        if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f)
            inBounds = 1;
    } else if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f) {
        inBounds = 1;
    }
    if (inBounds) {
        SetLife(plane, x, y, 0xff);
        if ((selectedLife & 0x78) == 0x60)
            SetLife(plane, x + Dx8[(selectedLife ^ 0xfc) & 7],
                    y + Dy8[(selectedLife ^ 0xfc) & 7], 0xfe);
        MeLocX = x;
        MeLocY = y;
        MeDir = selectedLife & 7;
        MeType = selectedLife & 0x78;
        MePlane = plane;
    }
    if (MeType < 8)
        MeEgg = MeDir;
    return 1;
}
