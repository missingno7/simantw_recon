/*
 * MysteryButton: cheat/debug dispatcher.  Picks one of 15 random actions
 * via RRand(15) and a dense jump table.  0/1 add red ants (twice) and
 * refresh the population count; 2 does the same for black ants; 3 kills
 * some ants (which=0) twice, 4 kills some ants (which=1) twice; 5 adds
 * food; 6 rescans the whole 128x64 Map[] grid, replacing every food tile
 * (IsItFood) with a fresh SRand16() byte and clearing FoodA; 7 plays a
 * sound list; 8/9 punch a ring of new holes (MakeNewHoleR/B) around the
 * yard; 10 clears AlwaysHealthy/HealthB/HealthR; 11 toggles a private
 * Dx8-segment flag (0x8a5c) and beeps one of two ways; 12 toggles a
 * second private Dx8-segment flag (0x8a5a) silently; 13 shows two
 * PictStrnDialog topics with a sound in between; 14 sets the private
 * near MeSMode latch to 8 and beeps.
 */
extern int far ListIndexA;
extern int far CommandKey;
extern int far FoodA;
extern int near AlwaysHealthy;
extern int near HealthB;
extern int near HealthR;
extern int near MeSMode;
extern unsigned char near Map[];
extern unsigned char far Dx8[];

extern int far RRand(int range);
extern void far AddRedAnts(int count);
extern void far AddBlackAnts(int count);
extern void far FullCount(void);
extern void far KillSomeAnts(int which);
extern void far AddFood(int a, int b);
extern void far myBeginSoundReverse(unsigned int first, unsigned int second, unsigned int third);
extern void far myBeginSoundList(int index);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern int far IsItFood(int tile);
extern int far SRand16(void);
extern void far MakeNewHoleR(int x);
extern void far MakeNewHoleB(int x);
extern void far PictStrnDialog(int a, int id, int c);

void far MysteryButton(void)
{
    int index;

    index = RRand(0xf);

    switch (index) {
    case 0:
    case 1: {
        int pop = ListIndexA;
        int amount;
        if (pop < 1000) {
            if (CommandKey == 1)
                amount = -(pop - 1000);
            else
                amount = 0x20;
            AddRedAnts(amount);
        }
        FullCount();
        pop = ListIndexA;
        if (pop < 1000) {
            if (CommandKey == 1)
                amount = -(pop - 1000);
            else
                amount = 0x20;
            AddRedAnts(amount);
        }
        FullCount();
        break;
    }

    case 2: {
        int pop = ListIndexA;
        int amount;
        if (pop < 1000) {
            if (CommandKey == 1)
                amount = -(pop - 1000);
            else
                amount = 0x20;
            AddBlackAnts(amount);
        }
        FullCount();
        pop = ListIndexA;
        if (pop < 1000) {
            if (CommandKey == 1)
                amount = -(pop - 1000);
            else
                amount = 0x20;
            AddBlackAnts(amount);
        }
        FullCount();
        break;
    }

    case 3:
        KillSomeAnts(0);
        KillSomeAnts(0);
        break;

    case 4:
        KillSomeAnts(1);
        KillSomeAnts(1);
        break;

    case 5:
        AddFood(1, 0x96);
        break;

    case 6: {
        int row, col;
        myBeginSoundReverse(0x20, 0, 0x7e);
        for (row = 0; row < 0x2000; row += 0x40) {
            for (col = 0; col < 0x40; col++) {
                int tile = Map[row + col];
                if (IsItFood(tile) == 1)
                    Map[row + col] = (unsigned char)SRand16();
            }
        }
        FoodA = 0;
        return;
    }

    case 7:
        myBeginSoundList(0);
        break;

    case 8: {
        int i;
        for (i = 0; i < 0x40; i += 2)
            MakeNewHoleR(i);
        return;
    }

    case 9: {
        int i;
        for (i = 0; i < 0x40; i += 2)
            MakeNewHoleB(i);
        return;
    }

    case 10:
        AlwaysHealthy = 0;
        HealthB = 0;
        HealthR = 0;
        return;

    case 11: {
        int newval = (*(int far *)&Dx8[0x8a5c] < 1) ? 1 : 0;
        *(int far *)&Dx8[0x8a5c] = newval;
        if (newval == 0)
            myBeginSound(1, 0, 0x7e);
        else
            myBeginSound(2, 0, 0x7e);
        break;
    }

    case 12: {
        int newval = (*(int far *)&Dx8[0x8a5a] < 1) ? 1 : 0;
        *(int far *)&Dx8[0x8a5a] = newval;
        break;
    }

    case 13:
        PictStrnDialog(0, 0x2726, 0);
        myBeginSoundList(1);
        PictStrnDialog(0, 0x2728, 0);
        break;

    case 14:
        MeSMode = 8;
        myBeginSound(2, 0x2b77, 0x7e);
        break;

    default:
        break;
    }
}
