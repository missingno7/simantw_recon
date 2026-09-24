/*
 * _DoWater source hypothesis from its closed instruction stream.
 * Segment-9/8 objects use exact MAPSYM names; MapA/B/R use the known
 * DGROUP arrays. The list loops and tile thresholds follow the packet.
 */
extern int near RainOn;
extern int far TERRAINset;
extern int far ClearRainFlag;
extern int far WaterTable;
extern unsigned char far RyTab[];
extern unsigned char far RxTab[];
extern unsigned char near MapA[64][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];

extern int far SRand1(int range);
extern void far myBeginSound(unsigned int first,
                             unsigned int second,
                             unsigned int third);
extern void far DrownBList(int y);
extern void far DrownRList(int y);
extern void far ZapEuMapAt(int plane, int x, int y);
extern void far PlaceDrop(int value);

void far DoWater(void)
{
    int i;
    int x;
    int y;
    int value;
    int far *waterPtr;

    if (RainOn != 0 && TERRAINset == 0) {
        if (SRand1(0x32) == 0)
            myBeginSound(0x29, 0, 0x40);

        ClearRainFlag = 1;

        if (SRand1(10) == 0) {
            waterPtr = &WaterTable;
            if (*waterPtr > 4) {
                --*waterPtr;
                y = *waterPtr;
                DrownBList(y);
                DrownRList(y);

                for (x = 0; x < 64; ++x) {
                    value = MapB[x][y];
                    if (value < 0x20)
                        value = 0x4e;
                    else
                        value += 0x2f;
                    MapB[x][y] = value;

                    value = MapR[x][y];
                    if (value < 0x20)
                        value = 0x4e;
                    else
                        value += 0x2f;
                    MapR[x][y] = value;

                    ZapEuMapAt(2, x, y);
                    ZapEuMapAt(3, x, y);
                }
            }
        }

        for (i = 0; i < 100; ++i) {
            y = RyTab[i];
            x = RxTab[i];
            value = MapA[x][y];
            if (value >= 0x74 && value < 0x77) {
                MapA[x][y] = value + 1;
            } else if (value == 0x77) {
                MapA[x][y] = SRand1(14);
                PlaceDrop(i);
            }
        }
        return;
    }

    if (TERRAINset == 0 && ClearRainFlag == 1) {
        ClearRainFlag = 0;
        for (i = 0; i < 100; ++i) {
            y = RyTab[i];
            x = RxTab[i];
            value = MapA[x][y];
            if (value >= 0x74 && value <= 0x77) {
                MapA[x][y] = SRand1(14);
                PlaceDrop(i);
            }
        }
    }

    waterPtr = &WaterTable;
    y = *waterPtr;
    if (y < 0x40 && SRand1(10) == 0) {
        for (x = 0; x < 64; ++x) {
            value = MapB[x][y];
            if (value == 0x4e)
                value = SRand1(8);
            MapB[x][y] = value - 0x2f;

            value = MapR[x][y];
            if (value == 0x4e)
                value = SRand1(8);
            MapR[x][y] = value - 0x2f;

            ZapEuMapAt(2, x, y);
            ZapEuMapAt(3, x, y);
        }
    }
}
