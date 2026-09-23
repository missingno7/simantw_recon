/* Scatter five-piece rocks, then twice as many three-piece rocks. */
extern int far SRand1(int range);
extern void far AddRock5(int x, int y, int shape);
extern void far AddRock3(int x, int y, int shape);

void far AddRocks(void)
{
    int count;
    int remaining;

    count = SRand1(3) + 2;
    if (count > 0) {
        remaining = count;
        do {
            AddRock5(SRand1(122), SRand1(58), 0);
            AddRock5(SRand1(122), SRand1(58), 1);
            AddRock5(SRand1(122), SRand1(58), 2);
            AddRock5(SRand1(122), SRand1(58), 3);
            AddRock5(SRand1(122), SRand1(58), 4);
            AddRock5(SRand1(122), SRand1(58), 5);
        } while (--remaining != 0);
    }
    if (count * 2 > 0) {
        remaining = count * 2;
        do {
            AddRock3(SRand1(124), SRand1(60), 0);
            AddRock3(SRand1(124), SRand1(60), 1);
            AddRock3(SRand1(124), SRand1(60), 2);
            AddRock3(SRand1(124), SRand1(60), 3);
            AddRock3(SRand1(124), SRand1(60), 4);
            AddRock3(SRand1(124), SRand1(60), 5);
        } while (--remaining != 0);
    }
}
