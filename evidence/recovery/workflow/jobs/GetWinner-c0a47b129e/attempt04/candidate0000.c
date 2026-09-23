/*
 * GetWinner: resolve combat between two ant identifiers a and b, each
 * encoding a team in bit 0x80 and a level-ish index in bits 0x78. While
 * Invincible, RAntsKilled (long) is incremented and the winner is b if
 * a's bit 0x80 is set, else a. Otherwise a combat-odds table indexed by
 * both combatants' (id&0x78)>>3 nibble picks a threshold (private near
 * tables at DGROUP 0x22c6 [16 bytes] and 0x22d6 [size undetermined,
 * indexed up to (15<<2)+15]; no MAPSYM/byte evidence surfaced for their
 * contents, so placeholder zeros are used) that RRand(10) is compared
 * against; the loser's side is charged (BlackLost/BAntsKilled if the
 * winner's bit 0x80 is set, else RedLost/RAntsKilled) and the winner
 * (a or b, whichever "won") is returned. Plain ret/push-bp prologue:
 * this is a near function.
 */
extern int far Invincible;
extern long far RAntsKilled;
extern int far BlackLost;
extern long far BAntsKilled;
extern int far RedLost;

extern int far RRand(int range);

static unsigned char near combatLevel[16] = {
    0, 0, 0, 0, 2, 0, 1, 1, 2, 1, 0, 0, 3, 3, 0, 0
};
static unsigned char near combatOdds[16] = {
    5, 2, 7, 3, 8, 5, 9, 4, 3, 1, 5, 2, 7, 6, 8, 5
};

int near GetWinner(int a, int b)
{
    int levelA;
    int levelB;
    int threshold;

    if (Invincible == 1) {
        RAntsKilled++;
        if (a & 0x80)
            return b;
        return a;
    }

    levelA = combatLevel[(a & 0x78) >> 3];
    levelB = combatLevel[(b & 0x78) >> 3];
    threshold = combatOdds[(levelA << 2) + levelB];

    if (RRand(10) >= threshold) {
        if (b & 0x80) {
            BlackLost++;
            BAntsKilled++;
        } else {
            RedLost++;
            RAntsKilled++;
        }
        return b;
    }

    if (a & 0x80) {
        BlackLost++;
        BAntsKilled++;
    } else {
        RedLost++;
        RAntsKilled++;
    }
    return a;
}
