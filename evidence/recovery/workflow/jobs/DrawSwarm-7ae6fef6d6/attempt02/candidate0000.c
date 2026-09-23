/*
 * Draw the black and red swarms around the yard swarm center.  MaintainSwarm
 * establishes the counts against queen storage; the packed signed coordinate
 * arrays hold each rendered insect's offset.  Invalid offsets are reset or
 * randomized as observed, cached objects are positioned, missing objects are
 * added, and handles past the active range are removed.
 */
extern int far MapMode;
extern int far CurYardPnt[2];
extern int far SwarmCentX;
extern int far SwarmCentY;
extern signed char far SwarmXB[];
extern signed char far SwarmYB[];
extern signed char far SwarmXR[];
extern signed char far SwarmYR[];
extern int far SwarmCntB;
extern int far SwarmCntR;
extern int near QueenStorageB;
extern int near QueenStorageR;
extern int near yardAnimHandle;
extern int far SRand16(void);
extern int far SRand1(int range);
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);
extern int far hanim_RemoveAnimObject(int animation, int object, int size);

static int near swarmObjectsB[16] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1
};
static int near swarmObjectsR[16] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1
};

void far DrawSwarm(void)
{
    int far *centerX;
    int far *centerY;
    signed char far *xB;
    signed char far *yB;
    signed char far *xR;
    signed char far *yR;
    int near *object;
    int i;
    int x;
    int y;
    int right;
    int bottom;

    if (MapMode != 0)
        return;

    centerY = &SwarmCentY;
    *centerY = CurYardPnt[1] * 10 + 0x2e;
    centerX = &SwarmCentX;
    *centerX = CurYardPnt[0] * 0x1c - CurYardPnt[1] + 0xb2;

    i = 0;
    object = swarmObjectsB;
    while (SwarmCntB > i && object < &swarmObjectsB[16] &&
           QueenStorageB > i) {
        yB = &SwarmYB[i];
        xB = &SwarmXB[i];
        y = *yB;
        x = *xB;
        if (x > 15 || x < -15 || y > 15 || y < -15) {
            x = SRand16() - 10;
            y = SRand16() - 10;
            x += SRand1(3) - 1;
            y += SRand1(3) - 1;
            *xB = (signed char)x;
            *yB = (signed char)y;
        }
        right = *centerX + x;
        bottom = *centerY + y;
        if (*object != -1)
            hanim_SetObjectPos(right, bottom, 0x1b5e, yardAnimHandle,
                               *object, -1);
        else
            *object = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                          0x1b5e, -1);
        ++i;
        ++object;
    }
    for (; object < &swarmObjectsB[16]; ++object) {
        if (*object != -1) {
            hanim_RemoveAnimObject(yardAnimHandle, *object, 0x1974);
            *object = -1;
        }
    }

    i = 0;
    object = swarmObjectsR;
    while (SwarmCntR > i && object < &swarmObjectsR[16] &&
           QueenStorageR > i) {
        yR = &SwarmYR[i];
        xR = &SwarmXR[i];
        y = *yR;
        x = *xR;
        if (x > 15 || x < -15 || y > 15 || y < -15) {
            *xR = 0;
            *yR = 0;
            x = SRand1(3) - 1;
            y = SRand1(3) - 1;
            *xR = (signed char)x;
            *yR = (signed char)y;
        }
        right = *centerX + x;
        bottom = *centerY + y;
        if (*object != -1)
            hanim_SetObjectPos(right, bottom, 0x1b5f, yardAnimHandle,
                               *object, -1);
        else
            *object = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                          0x1b5f, -1);
        ++i;
        ++object;
    }
    for (; object < &swarmObjectsR[16]; ++object) {
        if (*object != -1) {
            hanim_RemoveAnimObject(yardAnimHandle, *object, 0x197b);
            *object = -1;
        }
    }
}
