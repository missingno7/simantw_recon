/*
 * Render the black and red swarms around the yard swarm center.  The admitted
 * maintenance routine establishes count/queen bounds.  The packed signed
 * offsets are repaired when outside +/-15, then cached animation objects are
 * repositioned or added; stale handles after each active range are removed.
 */
extern int far MapMode;
extern volatile int far CurYardPnt[2];
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
    signed char far * volatile xDataB;
    signed char far * volatile yDataB;
    signed char far * volatile xDataR;
    signed char far * volatile yDataR;
    int far * volatile centerX;
    int far * volatile centerY;
    register int i;
    register int near *object;
    int bottom;
    int x;
    int y;
    int randomize;

    if (MapMode != 0)
        return;

    centerY = &SwarmCentY;
    centerX = &SwarmCentX;
    *centerY = CurYardPnt[1] * 10 + 0x2e;
    *centerX = CurYardPnt[0] * 0x1c - CurYardPnt[1] + 0xb2;

    xDataB = SwarmXB;
    yDataB = SwarmYB;
    i = 0;
    object = swarmObjectsB;
    if (SwarmCntB > 0) {
        do {
            if (object >= &swarmObjectsB[16] || QueenStorageB <= i)
                break;
            
            
            x = xDataB[i];
            y = yDataB[i];
            randomize = 0;
            if (x > 15 || x < -15 || y > 15 || y < -15)
                randomize = 1;
            if (randomize) {
                x = SRand16() - 10;
                y = SRand16() - 10;
                x += SRand1(3) - 1;
                y += SRand1(3) - 1;
                xDataB[i] = (signed char)x;
                yDataB[i] = (signed char)y;
            }
            bottom = *centerY + y;
            if (*object != -1)
                hanim_SetObjectPos(*centerX + x, bottom, 0x1b5e,
                                   yardAnimHandle, *object, -1);
            else
                *object = hanim_AddAnimObject(yardAnimHandle,
                        *centerX + x, bottom, 0x1b5e, -1);
            ++object;
            ++i;
        } while (SwarmCntB > i);
    }
    for (; object < &swarmObjectsB[16]; ++object) {
        if (*object != -1) {
            hanim_RemoveAnimObject(yardAnimHandle, *object, 0x1974);
            *object = -1;
        }
    }

    xDataR = SwarmXR;
    yDataR = SwarmYR;
    i = 0;
    object = swarmObjectsR;
    if (SwarmCntR > 0) {
        do {
            if (object >= &swarmObjectsR[16] || QueenStorageR <= i)
                break;
            
            
            x = xDataR[i];
            y = yDataR[i];
            randomize = 0;
            if (x > 15 || x < -15 || y > 15 || y < -15)
                randomize = 1;
            if (randomize) {
                xDataB[i] = 0;
                yDataB[i] = 0;
                x = SRand1(3) - 1;
                y = SRand1(3) - 1;
                xDataR[i] = (signed char)x;
                yDataR[i] = (signed char)y;
            }
            bottom = *centerY + y;
            if (*object != -1)
                hanim_SetObjectPos(*centerX + x, bottom, 0x1b5f,
                                   yardAnimHandle, *object, -1);
            else
                *object = hanim_AddAnimObject(yardAnimHandle,
                        *centerX + x, bottom, 0x1b5f, -1);
            ++object;
            ++i;
        } while (SwarmCntR > i);
    }
    for (; object < &swarmObjectsR[16]; ++object) {
        if (*object != -1) {
            hanim_RemoveAnimObject(yardAnimHandle, *object, 0x197b);
            *object = -1;
        }
    }
}
