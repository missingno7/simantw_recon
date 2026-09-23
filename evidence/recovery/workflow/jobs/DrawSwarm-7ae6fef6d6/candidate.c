/*
 * Draw the two swarms around the yard swarm center.  The black and red signed
 * coordinate arrays provide offsets; entries outside +/-15 are repaired by
 * the observed random rules.  Six far-pointer locals name the two centers and
 * each colony's coordinate arrays, while sixteen near handles are repositioned
 * or added and then removed when their swarm falls below the active bound.
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
    register int i;
    register int near *object;
    int right;

    if (MapMode != 0)
        return;

    right = CurYardPnt[1] * 10 + 0x2e;
    centerY = &SwarmCentY;
    *centerY = right;
    right = CurYardPnt[0] * 0x1c - CurYardPnt[1] + 0xb2;
    centerX = &SwarmCentX;
    *centerX = right;

    i = 0;
    object = swarmObjectsB;
    if (SwarmCntB > 0) {
        do {
            if (object >= &swarmObjectsB[16] || QueenStorageB <= i)
                break;
            yB = &SwarmYB[i];
            xB = &SwarmXB[i];
            if (*xB > 15 || *xB < -15 || *yB > 15 || *yB < -15) {
                *xB = (signed char)(SRand16() - 10);
                *yB = (signed char)(SRand16() - 10);
                *xB += (signed char)(SRand1(3) - 1);
                *yB += (signed char)(SRand1(3) - 1);
            }
            right = *xB + *centerX;
            if (*object != -1)
                hanim_SetObjectPos(right, *yB + *centerY, 0x1b5e,
                                   yardAnimHandle, *object, -1);
            else
                *object = hanim_AddAnimObject(yardAnimHandle, right,
                        *yB + *centerY, 0x1b5e, -1);
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

    i = 0;
    object = swarmObjectsR;
    if (SwarmCntR > 0) {
        do {
            if (object >= &swarmObjectsR[16] || QueenStorageR <= i)
                break;
            yR = &SwarmYR[i];
            xR = &SwarmXR[i];
            if (*xR > 15 || *xR < -15 || *yR > 15 || *yR < -15) {
                *xR = 0;
                *yR = 0;
                *xR = (signed char)(SRand1(3) - 1);
                *yR = (signed char)(SRand1(3) - 1);
            }
            right = *xR + *centerX;
            if (*object != -1)
                hanim_SetObjectPos(right, *yR + *centerY, 0x1b5f,
                                   yardAnimHandle, *object, -1);
            else
                *object = hanim_AddAnimObject(yardAnimHandle, right,
                        *yR + *centerY, 0x1b5f, -1);
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
