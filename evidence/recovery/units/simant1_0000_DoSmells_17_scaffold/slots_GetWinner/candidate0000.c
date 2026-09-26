/* Resolve combat between two ant identifiers. The private initialized tables below are the verified 16-byte combat-level and combat-odds tables; the old draft comment claiming placeholder zeros was stale. */
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

    if (RRand(10) < threshold) {
        if (a & 0x80) {
            BlackLost++;
            BAntsKilled++;
        } else {
            RedLost++;
            RAntsKilled++;
        }
        return a;
    }

    if (b & 0x80) {
        BlackLost++;
        BAntsKilled++;
    } else {
        RedLost++;
        RAntsKilled++;
    }
    return b;
}

