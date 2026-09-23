/*
 * DoAntSim: master per-tick orchestrator for the ant simulation. Best-
 * effort partial reconstruction -- most of the 762-byte body touches
 * private, unnamed PACK counters and thresholds (frame/tick counters,
 * AI-difficulty timers, end-game bookkeeping) that direct_data_bindings
 * does not resolve to a MAPSYM name (only 7 of 68 far operands in the
 * packet are named: _NextFeed, _match_position, _ModePopB, _ModePopR,
 * _IsGameOver, _gGameNeedsSaving). The confidently evidenced structure:
 * a global tick counter wraps at 0x1000; every 32nd tick a per-plane
 * mode byte (bits 5-6 of match_position[0]) switches among four
 * per-plane simulation passes -- DoAntSimA/DoAntSimB/DoAntSimR/
 * DoAntSimY plus their matching CompactListA/CompactListB/CompactListR
 * calls (all already-admitted or unit-neighbour near_calls); a bit-0
 * flag zeroes two 0x14-word PACK score tables; ModePopB/ModePopR are
 * refreshed from population sub-totals; IsGameOver is checked and, if
 * set, gGameNeedsSaving is stamped. The exact per-branch call order,
 * private counter semantics and literal thresholds (0x1000, 0x96,
 * 0x32, 0x14, ...) are NOT independently confirmed here -- this file
 * is a structural placeholder, not a claimed exact match.
 */
/* Hypothesis: match_position is addressed through the SIMANT data-group selector and a literal displacement, as in the target load at entry. */
extern int __based(__segname("SIMANT_DATA_GROUP")) match_position[];
extern int far NextFeed;
extern int far ModePopB;
extern int far ModePopR;
extern int far IsGameOver;
extern int far gGameNeedsSaving;

extern void near DoAntSimA(void);
extern void near DoAntSimB(void);
extern void near DoAntSimR(void);
extern void near DoAntSimY(void);
extern void far CompactListA(void);
extern void far CompactListB(void);
extern void far CompactListR(void);
extern void far DoSimYard(void);
extern void far DoWater(void);
extern void far DoAntLions(void);
extern void far MoveSpider(void);
extern void far DoPillar(void);
extern int far GetStrategy(void);
extern void far Feedback(void);
extern void far EndGameDialog(void);

void far DoAntSim(void)
{
    int mode;

    if (++match_position[0x3afe] > 0x1000)
        match_position[0x3afe] = 0;

    mode = (((unsigned char far *)match_position)[0] & 0x60) >> 5;
    switch (mode) {
    case 0:
        DoAntSimA();
        CompactListA();
        break;
    case 1:
        DoAntSimR();
        CompactListR();
        break;
    case 2:
        DoAntSimB();
        CompactListB();
        break;
    case 3:
        DoAntSimY();
        break;
    default:
        break;
    }

    DoSimYard();
    DoWater();
    DoAntLions();
    MoveSpider();
    DoPillar();
    GetStrategy();

    if (IsGameOver != 0) {
        Feedback();
        gGameNeedsSaving = 1;
    }
}
