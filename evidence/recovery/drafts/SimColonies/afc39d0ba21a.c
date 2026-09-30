/* SimColonies: age the colony counts, evolve occupied map cells, and test
 * the two-colony game outcome. */
extern int far YardCycle;
extern int far ColonyUpdateFlag;
extern int far SwarmCntB;
extern int far SwarmCntR;
extern int far HouseColonies;
extern int far CurYardPnt[2];

extern int far CurGameType;
extern int far SwarmDelayB;
extern int far SwarmDelayR;
extern int far LastColonyPopB;
extern int far LastColonyPopR;
extern int far BColoniesKilled;
extern int far RColoniesKilled;
extern int far BColoniesStarted;
extern int far RColoniesStarted;
extern int far LayDownQueenMode;
extern int far IsGameOver;
extern int far BlackWon;
extern int far NodeNum;
extern int near BoyHere;
extern int near BoyFrame;
extern int near QueenStorageB;
extern int near QueenStorageR;
extern int near BpopT;
extern int near RpopT;
extern int near ColonyTotalBlack;
extern int near ColonyTotalRed;
extern int near ForSaleState;
extern int near CastePopB[6];
extern unsigned char far YMapPopB[192];
extern unsigned char far YMapPopR[192];
/* These private byte tables are already owned by the simtwo:1378 unit. */
extern unsigned char near PatchX[6];
extern unsigned char near PatchY[6];

extern int far SRand1(int range);
extern int far SRand8(void);
extern int far SGSRand(int range);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void far PictStrnDialog(int picture, int object, int force);
extern void far DrawSimPayoff(void);

void far SimColonies(void)
{
    int x;
    int y;
    int far * volatile queenXPtr;
    int far * volatile queenYPtr;
    int far *swarmBPtr;
    int patches;
    int b;
    int r;
    int direction;
    int nextX;
    int nextY;
    int value;

    __segment packSegment = __segname("PACK");
    unsigned char __based(packSegment) * volatile yardCycleByte;
    yardCycleByte = (unsigned char __based(packSegment) *)(unsigned int)&YardCycle;
    if ((*yardCycleByte & 0x1f) != 0)
        return;

    ColonyUpdateFlag = 1;

    swarmBPtr = &SwarmCntB;
    value = *swarmBPtr;
    if (value > 0) {
        if (value >= 4)
            value -= value >> 2;
        else
            --value;
    }
    if (QueenStorageB > value)
        value = QueenStorageB;
    if (value > 50)
        value = 50;
    *swarmBPtr = value;

    value = SwarmCntR;
    if (value > 0) {
        if (value >= 4)
            value -= value >> 2;
        else
            --value;
    }
    if (QueenStorageR > value)
        value = QueenStorageR;
    if (value > 50)
        value = 50;
    SwarmCntR = value;

    ColonyTotalBlack = 0;
    ColonyTotalRed = 0;
    HouseColonies = 0;
    if (BpopT > 0)
        ColonyTotalBlack = 1;
    if (RpopT > 0)
        ColonyTotalRed = 1;

    queenXPtr = &CurYardPnt[0];
    queenYPtr = &CurYardPnt[1];
    r = BpopT & 0x03ff;
    if (r > 250)
        r = 250;
    YMapPopB[((*queenXPtr) << 4) + (*queenYPtr)] = (unsigned char)r;
    r = RpopT & 0x03ff;
    if (r > 250)
        r = 250;
    YMapPopR[((*queenXPtr) << 4) + (*queenYPtr)] = (unsigned char)r;

    /* Visit the 12 by 16 yard.  Each occupied site gains or loses population
     * according to the six neighboring color counts. */
    for (x = 0; x < 12; ++x) {
        for (y = 0; y < 16; ++y) {
            if (x == (*queenXPtr) && y == (*queenYPtr))
                continue;

            r = YMapPopR[(x << 4) + y];
            b = YMapPopB[(x << 4) + y];
            if (b == 0 && r == 0)
                continue;

            if (CurGameType == 2 && (x < 2 || (x == 3 && y < 5)))
                ++HouseColonies;

            patches = 0;
            for (direction = 0; direction < 6; ++direction) {
                nextX = x + PatchX[direction];
                nextY = y + PatchY[direction];
                if (nextX >= 0 && nextX < 12 &&
                    nextY >= 0 && nextY < 16) {
                    if (YMapPopB[(nextX << 4) + nextY] != 0)
                        patches += 3;
                    if (YMapPopR[(nextX << 4) + nextY] != 0)
                        patches -= 3;
                }
            }

            if (b != 0) {
                ++ColonyTotalBlack;
                if (patches != 0)
                    b += patches;
                else
                    ++b;
                if (b <= 0) {
                    ++BColoniesKilled;
                    YMapPopB[(x << 4) + y] = 0;
                } else if (b >= 250) {
                    YMapPopB[(x << 4) + y] = 250;
                    if (SRand1(10) == 0) {
                        nextX = x + SGSRand(4);
                        nextY = y + SGSRand(4);
                        if (nextX < 0)
                            nextX = 0;
                        if (nextX > 11)
                            nextX = 11;
                        if (nextY < 0)
                            nextY = 0;
                        if (nextY > 15)
                            nextY = 15;
                        if (nextX != x || nextY != y) {
                                    if (YMapPopB[(nextX << 4) + nextY] == 0) {
                                ++BColoniesStarted;
                                ++YMapPopB[(nextX << 4) + nextY];
                            }
                        }
                    }
                } else {
                    YMapPopB[(x << 4) + y] = (unsigned char)b;
                }
            }

            if (r != 0) {
                ++ColonyTotalRed;
                if (patches != 0)
                    r -= patches;
                else
                    ++r;
                if (r <= 0) {
                    ++RColoniesKilled;
                    YMapPopR[(x << 4) + y] = 0;
                    if (x == 11) {
                        y = 8;
                        YMapPopR[(SRand1(6) + 2) << 4] = 20;
                    }
                } else if (r >= 250) {
                    YMapPopR[(x << 4) + y] = 250;
                    if (SRand1(10) == 0) {
                        nextX = x + SGSRand(4);
                        nextY = y + SGSRand(4);
                        if (nextX < 0)
                            nextX = 0;
                        if (nextX > 11)
                            nextX = 11;
                        if (nextY < 0)
                            nextY = 0;
                        if (nextY > 15)
                            nextY = 15;
                        if (nextX != x || nextY != y) {
                                    if (YMapPopR[(nextX << 4) + nextY] == 0) {
                                ++RColoniesStarted;
                                ++YMapPopR[(nextX << 4) + nextY];
                            }
                        }
                    }
                } else {
                    YMapPopR[(x << 4) + y] = (unsigned char)r;
                }
            }
        }
    }

    /* A delay event spends queen storage to start new cells near the queen. */
    if (LayDownQueenMode == 1) {
        ++SwarmDelayB;
        if (SRand8() + 10 < SwarmDelayB) {
            SwarmDelayB = 0;
            while (QueenStorageB > 0) {
                nextX = (*queenXPtr) + SGSRand(4);
                nextY = (*queenYPtr) + SGSRand(4);
                if (nextX < 0)
                    nextX = 0;
                if (nextX > 11)
                    nextX = 11;
                if (nextY < 0)
                    nextY = 0;
                if (nextY > 15)
                    nextY = 15;
                if ((nextX != (*queenXPtr) || nextY != (*queenYPtr)) &&
                    YMapPopB[(nextX << 4) + nextY] == 0) {
                    ++BColoniesStarted;
                    ++YMapPopB[(nextX << 4) + nextY];
                }
                --QueenStorageB;
            }
        }
    }

    ++SwarmDelayR;
    if (SRand8() + 10 < SwarmDelayR) {
        SwarmDelayR = 0;
        while (QueenStorageR > 0) {
            nextX = (*queenXPtr) + SGSRand(4);
            nextY = (*queenYPtr) + SGSRand(4);
            if (nextX < 0)
                nextX = 0;
            if (nextX > 11)
                nextX = 11;
            if (nextY < 0)
                nextY = 0;
            if (nextY > 15)
                nextY = 15;
            if ((nextX != (*queenXPtr) || nextY != (*queenYPtr)) &&
                YMapPopR[(nextX << 4) + nextY] == 0) {
                ++RColoniesStarted;
                ++YMapPopR[(nextX << 4) + nextY];
            }
            --QueenStorageR;
        }
    }

    if (CurGameType != 2)
        return;

    if (ColonyTotalRed == 0 && LastColonyPopR != 0) {
        myBeginSong(0x4e22, 0x7e);
        PictStrnDialog(0, 0x2744, 1);
        if (ForSaleState == 0)
            PictStrnDialog(0, 0x2747, 1);
    }

    LastColonyPopB = ColonyTotalBlack;
    LastColonyPopR = ColonyTotalRed;

    if (ForSaleState == 0 && HouseColonies > 0x18) {
        ForSaleState = 1;
        NodeNum = 0;
        BoyHere = 0;
        BoyFrame = -1;
        myBeginSong(0x4e23, 0x7e);
        PictStrnDialog(0, 0x2746, 1);
        if (ColonyTotalRed != 0)
            PictStrnDialog(0, 0x2745, 1);
    }

    if (ForSaleState != 0 && ColonyTotalRed == 0) {
        myBeginSong(0x4e25, 0x7e);
        PictStrnDialog(0, 0x2749, 1);
        IsGameOver = 1;
        BlackWon = 1;
        DrawSimPayoff();
        return;
    }

    if (ColonyTotalBlack < 2 && CastePopB[5] == 0 &&
        CastePopB[0] == 0 && CastePopB[3] == 0 && CastePopB[4] == 0) {
        IsGameOver = 1;
        BlackWon = 0;
        PictStrnDialog(0, 0x2748, 1);
    }
}

