/*
 * DoRepoFly: a repopulation ant (generic A list, index ant) trying to fly
 * away.  red = colony bit of its AlistT byte.  With probability 1/32
 * (SRand32() == 0) and while the colony's swarm count (SwarmCntB / SwarmCntR)
 * is below 50, the ant leaves the map: its type byte is cleared and its
 * LifeA cell (AlistX & 0xff, AlistY) erased.  In game type 2 the colony's
 * swarm count grows and, one time in sixteen (SRand16), the matching queen
 * storage counter (QueenStorageB with a display invalidation, or
 * QueenStorageR) is incremented.  A-list fields are the public based arrays
 * of SIMANT_DATA_GROUP; the two zero stores are separate statements so the
 * ant index register is free for the LifeA row load.
 */
extern unsigned char near LifeA[128][64];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern int far SwarmCntB;
extern int far SwarmCntR;
extern int far CurGameType;
extern int near QueenStorageB;
extern int near QueenStorageR;

extern int far SRand32(void);
extern int far SRand16(void);
extern void far InvalQueenStorageDisp(void);

void near DoRepoFly(int ant)
{
    int red;

    red = AlistT[ant] & 0x80;
    if (SRand32() == 0) {
        if ((red == 0 && SwarmCntB < 50) || (red != 0 && SwarmCntR < 50)) {
            AlistT[ant] = 0;
            LifeA[AlistX[ant] & 0xff][AlistY[ant]] = 0;
            if (CurGameType == 2) {
                if (red == 0)
                    SwarmCntB++;
                else
                    SwarmCntR++;
                if (SRand16() == 0) {
                    if (red == 0) {
                        QueenStorageB++;
                        InvalQueenStorageDisp();
                    } else
                        QueenStorageR++;
                }
            }
        }
    }
}
