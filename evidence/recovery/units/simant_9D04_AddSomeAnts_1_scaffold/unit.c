/* Candidate translation unit simant_9D04_AddSomeAnts_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _AddSomeAnts
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

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
            if (kind == 1)
                AddBlackAnts(1000 - count);
            else
                AddRedAnts(1000 - count);
        } else if (kind == 1) {
            AddBlackAnts(0x20);
        } else {
            AddRedAnts(0x20);
        }
    }
    FullCount();
}

