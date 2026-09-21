/*
 * GetNewRedTask: choose the red colony's next initiator task.
 *
 * Always calls UnRecruitRed() first. When MePlane==1 and a randomized
 * threshold (SRand1(32)+64) stays below MeLocX, and a second random
 * draw (SRand1(10)) stays below the far "recruit gate" count, RedTask
 * is set to 2 (aggressive recruit) and RecruitRed(gate) is called with
 * that same count, then returns.
 *
 * Otherwise (either MePlane!=1 or either random gate failed): mirror
 * the red queen's Y/X position (far Dx8-segment fields, hypothesis
 * names redQueenY/redQueenX) into two far tuning values (redAggro,
 * redAggroLimit); when redQueenX<=30, nudge redAggro toward the
 * [20,40] band by +-5; otherwise reduce redAggroLimit by 5. Finally,
 * recruit a count derived from the sum of two near values (hypothesis
 * names redFactorA/redFactorB): (sum>>2) while the sum is below 20,
 * else (sum>>3); set RedTask to 1.
 *
 * Declarations for the unnamed far/near operands are hypotheses from
 * their observed offsets and arithmetic role; no MAPSYM name was
 * surfaced for them in the inspection packet.
 */
extern int far MePlane;
extern int far MeLocX;
extern int far RedTask;
extern int far redQueenX;
extern int far redQueenY;
extern int far redRecruitGate;
extern int far redAggro;
extern int far redAggroLimit;
extern int near redFactorA;
extern int near redFactorB;

extern void far UnRecruitRed(void);
extern int far SRand1(int range);
extern void far RecruitRed(int count);

void far GetNewRedTask(void)
{
    int sum;

    UnRecruitRed();

    if (MePlane == 1) {
        if (SRand1(32) + 0x40 < MeLocX) {
            if (SRand1(10) < redRecruitGate) {
                RedTask = 2;
                RecruitRed(redRecruitGate);
                return;
            }
        }
    }

    redAggro = redQueenY;
    redAggroLimit = redQueenX;
    if (redQueenX <= 0x1e) {
        if (redAggro < 0x14)
            redAggro += 5;
        else if (redAggro > 0x28)
            redAggro -= 5;
    } else {
        redAggroLimit -= 5;
    }

    sum = redFactorA + redFactorB;
    if (sum < 0x14)
        RecruitRed(sum >> 2);
    else
        RecruitRed(sum >> 3);
    RedTask = 1;
}
