/*
 * MaintainSwarm: decay and clamp the two colonies' swarm counters.  For
 * each colony the far PACK counter (SwarmCntB at PACK 0x807a, SwarmCntR at
 * 0x9c26; the segment is loaded as an immediate, which MSC emits for far
 * array objects as in the verified match_position convention) is reduced
 * when positive: by a quarter (arithmetic shift) when at least 4,
 * otherwise by one; the expressions read the counter directly, which is
 * why the subtraction re-reads it after the shift.  The result is then
 * raised to at least the colony's near QueenStorage word (QueenStorageB,
 * QueenStorageR, read through SS while DS/ES select PACK) and capped at
 * 50 before being stored back once.
 */
extern int far match_position[];
extern int near QueenStorageB;
extern int near QueenStorageR;

void far MaintainSwarm(void)
{
    int n;

    if (match_position[0x403d] > 0) {
        if (match_position[0x403d] >= 4)
            n = match_position[0x403d] - (match_position[0x403d] >> 2);
        else
            n = match_position[0x403d] - 1;
    } else
        n = match_position[0x403d];
    if (QueenStorageB > n)
        n = QueenStorageB;
    if (n > 50)
        n = 50;
    match_position[0x403d] = n;

    if (match_position[0x4e13] > 0) {
        if (match_position[0x4e13] >= 4)
            n = match_position[0x4e13] - (match_position[0x4e13] >> 2);
        else
            n = match_position[0x4e13] - 1;
    } else
        n = match_position[0x4e13];
    if (QueenStorageR > n)
        n = QueenStorageR;
    if (n > 50)
        n = 50;
    match_position[0x4e13] = n;

}
