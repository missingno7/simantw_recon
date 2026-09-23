/*
 * Draw the black and red swarms around the yard's swarm center.  The packed
 * coordinate arrays provide signed offsets; invalid offsets are re-randomized
 * inside the observed +/-15 range.  Each colony has sixteen cached animation
 * handles, which are repositioned or added and then cleared beyond the active
 * queen-storage/count limit.
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
    int i;
    int right;
    int bottom;
    signed char x;
    signed char y;

    if (MapMode != 0)
        return;

    SwarmCentY = CurYardPnt[1] * 10 + 0x2e;
    SwarmCentX = CurYardPnt[0] * 0x1c - CurYardPnt[1] + 0xb2;

    for (i = 0; i < 16 && i < SwarmCntB && i < QueenStorageB; ++i) {
        x = SwarmXB[i];
        y = SwarmYB[i];
        if (x > 15 || x < -15 || y > 15 || y < -15) {
            x = (signed char)(SRand16() - 10);
            y = (signed char)(SRand16() - 10);
            x = (signed char)(x + SRand1(3) - 1);
            y = (signed char)(y + SRand1(3) - 1);
            SwarmXB[i] = x;
            SwarmYB[i] = y;
        }
        right = SwarmCentX + x;
        bottom = SwarmCentY + y;
        if (swarmObjectsB[i] != -1) {
            hanim_SetObjectPos(right, bottom, 0x1b5e, yardAnimHandle,
                               swarmObjectsB[i], -1);
        } else {
            swarmObjectsB[i] = hanim_AddAnimObject(yardAnimHandle, right,
                                                    bottom, 0x1b5e, -1);
        }
    }
    for (; i < 16; ++i) {
        if (swarmObjectsB[i] != -1) {
            hanim_RemoveAnimObject(yardAnimHandle, swarmObjectsB[i], 0x1974);
            swarmObjectsB[i] = -1;
        }
    }

    for (i = 0; i < 16 && i < SwarmCntR && i < QueenStorageR; ++i) {
        x = SwarmXR[i];
        y = SwarmYR[i];
        if (x > 15 || x < -15 || y > 15 || y < -15) {
            SwarmXR[i] = 0;
            SwarmYR[i] = 0;
            x = (signed char)(SRand1(3) - 1);
            y = (signed char)(SRand1(3) - 1);
            SwarmXR[i] = x;
            SwarmYR[i] = y;
        }
        right = SwarmCentX + x;
        bottom = SwarmCentY + y;
        if (swarmObjectsR[i] != -1) {
            hanim_SetObjectPos(right, bottom, 0x1b5f, yardAnimHandle,
                               swarmObjectsR[i], -1);
        } else {
            swarmObjectsR[i] = hanim_AddAnimObject(yardAnimHandle, right,
                                                    bottom, 0x1b5f, -1);
        }
    }
    for (; i < 16; ++i) {
        if (swarmObjectsR[i] != -1) {
            hanim_RemoveAnimObject(yardAnimHandle, swarmObjectsR[i], 0x197b);
            swarmObjectsR[i] = -1;
        }
    }
}
