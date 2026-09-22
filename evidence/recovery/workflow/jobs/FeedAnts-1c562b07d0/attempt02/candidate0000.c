extern int near HealthB;
extern int near HealthR;
extern int far AlwaysHealthy[];
extern int far CurGameType[];
extern int far NextFeed[];
extern int far FoodA[];
extern void far AddFood(int amount, int kind);
extern int far SRand1(int limit);

/* FeedAnts: regenerate health, then feed if not out of food. */
void near FeedAnts(void)
{
    if (AlwaysHealthy[0x4530] == 0) {
        if (--HealthB < 0)
            HealthB = 0;
    }
    if (--HealthR < 0)
        HealthR = 0;
    if (CurGameType[0x405a] == 3)
        return;
    if (FoodA[0x4f42] >= NextFeed[0x4531])
        return;
    AddFood(0x96, 1);
    NextFeed[0x4531] = SRand1(0x32) + 1;
}
