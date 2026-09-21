/*
 * MaintainSwarm: decay and clamp the two colonies' swarm counters.  For
 * each colony the far PACK counter (SwarmCntB, SwarmCntR; selector loaded
 * as an immediate segment as in the verified DoAntSimB) is reduced when
 * positive: by a quarter (arithmetic shift) when at least 4, otherwise by
 * one.  The result is then raised to at least the colony's near
 * QueenStorage word (QueenStorageB, QueenStorageR, read through SS while
 * DS selects the PACK segment) and capped at 50 before being stored back.
 * The reduction re-reads the counter for the subtraction, so the
 * expressions use the counter directly and only the result is a local.
 */
extern int far SwarmCntB;
extern int far SwarmCntR;
extern int near QueenStorageB;
extern int near QueenStorageR;

void far MaintainSwarm(void)
{
    int n;

    n = SwarmCntB;
    if (n > 0) {
        if (n >= 4)
            n = SwarmCntB - (n >> 2);
        else
            n--;
    }
    if (QueenStorageB > n)
        n = QueenStorageB;
    if (n > 50)
        n = 50;
    SwarmCntB = n;

    n = SwarmCntR;
    if (n > 0) {
        if (n >= 4)
            n = SwarmCntR - (n >> 2);
        else
            n--;
    }
    if (QueenStorageR > n)
        n = QueenStorageR;
    if (n > 50)
        n = 50;
    SwarmCntR = n;
}
