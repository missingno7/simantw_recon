/*
 * Hypothesis: inspect the six nearby patch offsets, retain only coordinates
 * inside the 12 by 16 local map, and score the B/R population planes using
 * their observed far-object offsets.  The two private byte tables are kept
 * as near declarations; their exact historical placement is a separate
 * complete-member obligation.
 */
extern unsigned char near PatchX[];
extern unsigned char near PatchY[];
extern unsigned char far YMapPopB[];
extern unsigned char far YMapPopR[];

int far GetNearbyPatches(int x, int y)
{
    int index;
    register int offset;
    int count;
    register int patchX;
    register int patchY;

    count = 0;
    for (index = 0; index < 6; ++index) {
        patchY = PatchY[index] + y;
        patchX = PatchX[index] + x;
        if (patchX >= 0 && patchY >= 0 &&
            patchX < 12 && patchY < 16) {
            offset = (patchX << 4) + patchY;
            if (YMapPopB[(patchX << 4) + patchY + 0xa4] != 0)
                count += 3;
            if (YMapPopR[offset + 0x164] != 0)
                count -= 3;
        }
    }
    return count;
}
