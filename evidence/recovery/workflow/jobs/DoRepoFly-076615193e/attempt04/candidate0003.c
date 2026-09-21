/*
 * DoRepoFly: let an A-list reproductive ant fly away.  Its colour is
 * bit 7 of the list type byte (offset 0x2f62).  With a 1-in-32 chance,
 * and only while its colony's far swarm count (SwarmCntB or SwarmCntR)
 * is below 50, the ant is removed from the list and its LifeA cell
 * (row 0x23a4, column 0x278e); in game type 2 the colony's swarm count
 * grows and, with a further 1-in-16 chance, so does its queen storage
 * (the black display being invalidated).  The list bytes share one
 * selector slot (far byte addressed by offset).
 */
extern unsigned char near LifeA[128][64];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
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

    red = AT(ant + 0x2f62) & 0x80;
    if (SRand32() != 0) return;
    if (!red) { if (SwarmCntB >= 50) return; } else { if (SwarmCntR >= 50) return; }
    {
        AT(ant + 0x2f62) = 0;
        LifeA[AT(ant + 0x23a4) & 0xff][AT(ant + 0x278e)] = 0;
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
