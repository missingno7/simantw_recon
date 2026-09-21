/*
 * Hypothesis: maintain a maximum of 1000 A-list ants.  CommandKey selects
 * whether to add the remaining capacity or a fixed batch of 32, while the
 * formal flag selects the black or red ant helper.  FullCount is called on
 * every exit, including the already-full case.
 */
extern int far ListIndexA;
extern int far CommandKey;
extern void far AddBlackAnts(int count);
extern void far AddRedAnts(int count);
extern void far FullCount(void);

void far AddSomeAnts(int kind)
{
    int count;

    count = ListIndexA;
    if (count < 1000) {
        if (CommandKey == 1) {
            count = 1000 - count;
            if (kind == 1)
                AddBlackAnts(count);
            else
                AddRedAnts(count);
        } else if (kind == 1) {
            AddBlackAnts(0x20);
        } else {
            AddRedAnts(0x20);
        }
    }
    FullCount();
}
