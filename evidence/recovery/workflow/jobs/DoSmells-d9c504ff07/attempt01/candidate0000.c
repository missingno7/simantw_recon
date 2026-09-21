/*
 * Hypothesis: the PACK Cycle byte selects one of four smell-maintenance
 * passes from bits 5 and 6.  The three nonempty cases have the exact
 * same-segment and SIMONE calls recovered from the relative call targets;
 * case 3 intentionally does nothing.
 */
extern unsigned char far Cycle;

extern void far CompactListA(void);
extern void far CompactListB(void);
extern void far CompactListR(void);
extern void far FullCount(void);
extern void far HistUpdate(void);
extern void far FillHolesBN(void);
extern void far FillHolesRN(void);
extern void far ColonySmellBN(void);
extern void far ColonySmellRN(void);
extern void far ColonySmellBT(void);
extern void far ColonySmellRT(void);
extern void far SmoothAlarm(void);

void DoSmells(void)
{
    unsigned int mode;

    mode = (Cycle & 0x60) >> 5;
    switch (mode) {
    case 0:
        CompactListA();
        FullCount();
        HistUpdate();
        SmoothAlarm();
        break;
    case 1:
        CompactListB();
        FillHolesBN();
        ColonySmellBN();
        ColonySmellBT();
        break;
    case 2:
        CompactListR();
        FillHolesRN();
        ColonySmellRN();
        ColonySmellRT();
        break;
    }
}
