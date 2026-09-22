/* FeedAnts: regenerate colony health, then drop food into the yard unless
 * the game is out of food or in game type 3.
 *
 * Unit review: the grinder candidate reached the original bytes with bogus
 * `Symbol[0xNNNN]` spellings that add the symbol's own MAPSYM offset to the
 * symbol (the isolated matcher flags every such fixup as wrongly resolved).
 * The far scalars are simply the named far globals: AlwaysHealthy (segment 8,
 * 0x8A60), NextFeed (0x8A62), CurGameType (segment 9, 0x80B4), FoodA
 * (segment 9, 0x9E84); each is reached through its own selector-pool word.
 * Branch fix (agentNE3): HealthR is decremented unconditionally, only the
 * HealthB decrement is gated by AlwaysHealthy == 0. */
extern int near HealthB;
extern int near HealthR;
extern int far AlwaysHealthy;
extern int far CurGameType;
extern int far NextFeed;
extern int far FoodA;
extern void far AddFood(int amount, int kind);
extern int far SRand1(int limit);

void near FeedAnts(void)
{
    if (AlwaysHealthy == 0) {
        if (--HealthB < 0)
            HealthB = 0;
    }
    if (--HealthR < 0)
        HealthR = 0;
    if (CurGameType == 3)
        return;
    if (FoodA >= NextFeed)
        return;
    AddFood(0x96, 1);
    NextFeed = SRand1(0x32) + 1;
}
