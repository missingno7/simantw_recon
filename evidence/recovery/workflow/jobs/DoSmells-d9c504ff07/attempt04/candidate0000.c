/*
 * Hypothesis: the PACK Cycle byte selects one of four smell-maintenance
 * passes from bits 5 and 6.  The three nonempty cases have the exact
 * same-segment and SIMONE calls recovered from the relative call targets;
 * case 3 intentionally does nothing.
 */
extern int far Cycle;

extern void far CompactListA(void);
extern void far CompactListB(void);
extern void far CompactListR(void);
extern void far FullCount(void);
extern void far HistUpdate(void);
extern void near FillHolesBN(void);
extern void near FillHolesRN(void);
extern void near ColonySmellBN(void);
extern void near ColonySmellRN(void);
extern void near ColonySmellBT(void);
extern void near ColonySmellRT(void);
extern void near SmoothAlarm(void);

void near DoSmells(void)
{
    unsigned int mode;

    mode = (Cycle & 0x60) >> 5;
    if (mode == 0) {
        CompactListA();
        FullCount();
        HistUpdate();
        SmoothAlarm();
        return;
    }

    --mode;
    if (mode == 0) {
        CompactListB();
        FillHolesBN();
        ColonySmellBN();
        ColonySmellBT();
        return;
    }

    --mode;
    if (mode == 0) {
        CompactListR();
        FillHolesRN();
        ColonySmellRN();
        ColonySmellRT();
        return;
    }

    --mode;
}
