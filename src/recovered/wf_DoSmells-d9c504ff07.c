/*
 * DoSmells: one of four maintenance passes selected by bits 5-6 of the
 * PACK Cycle word.  Pass 0 compacts the A list and then does the pass-2 work
 * (full count, history update, alarm smoothing); pass 1 compacts the
 * B list and refreshes the black nest/trail smells, pass 3 does the same
 * for the red colony.  Pass 2 repeats the tail of pass 0, which the
 * compiler merges into a jump into the middle of the pass-0 body.
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
    switch ((Cycle & 0x60) >> 5) {
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
        FullCount();
        HistUpdate();
        SmoothAlarm();
        break;
    case 3:
        CompactListR();
        FillHolesRN();
        ColonySmellRN();
        ColonySmellRT();
        break;
    }
}
