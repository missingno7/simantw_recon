/* Semantic hypothesis: preserve the admitted shared food/life counters and reconstruct the object-specific result branches. */
/*
 * EatMyFood (SIMONE_MODULE, unit simone:5AD2, profile "og" ASSIGNED to this
 * unit; my ant object). Dispatches on mode=[bp+6] (0..3, default otherwise):
 *  0: myBeginSound(0x2c,0,0x7e); SetDefaultWindPrompt(1); -> health section.
 *  1: YellowDialog(0x2396,-1); then push WindPromptStrs[+0x2e/+0x2c] (a far
 *     long field) with duration 0x78 and jump straight into the shared
 *     EditMessage call (skipping the sound/delay dance).
 *  2: same but WindPromptStrs[+0x32/+0x30], duration 0x78.
 *  3 (and this is the only path that runs the full dance): myBeginSound
 *     (0x2c,0,0x7e); wait via mySoundIsDone()/myDelay(5) until done; a
 *     second myBeginSound(0xa,0,0x7e); reset EditMsgDelay; then
 *     EditMessage(WindPromptStrs[+0x36/+0x34], 0xb4, 0, 0).
 *  default: nothing shown, straight to the health section.
 * All of 0/1/2/3 except mode==2 then apply a health boost: if MeHealth was
 * still positive and mode!=1 and BpopT>1, spread MeHealth/(BpopT-1) into
 * the shared HealthB pool (clamped to 100); MeHealth is then unconditionally
 * set to 100. Finally: if MeHealth<=10, return; otherwise recompute a
 * "surplus" (MeHealth-10), clamp it via NeverHungry/[0,100], update
 * MeWarnHealth if the surplus exceeds it (min 10), set MeHealth=surplus,
 * and if MeWarnHealth<100 clear MeWantFood and return, else set it.
 *
 * Named globals confirmed via exact MAPSYM bindings: MeHealth, BpopT,
 * HealthB, MeHealthCntDwn, MeWarnHealth, NeverHungry, MeWantFood,
 * EditMsgDelay, WindPromptStrs (a far pointer to an array of message
 * records containing 32-bit position-like fields at +0x2c/0x30/0x34).
 */

extern int near MeHealth;
extern int near BpopT;
extern int near HealthB;
extern int far EditMsgDelay;
extern int far MeHealthCntDwn;
extern int far MeWarnHealth;
extern int far NeverHungry;
extern int far MeWantFood;

struct WindPrompt {
    char pad[0x2c];
    long pos0;   /* +0x2c/+0x2e */
    long pos1;   /* +0x30/+0x32 */
    long pos2;   /* +0x34/+0x36 */
};

extern struct WindPrompt far *WindPromptStrs;

extern void far myBeginSound(unsigned int a, unsigned int b, unsigned int c);
extern void far SetDefaultWindPrompt(int flag);
extern void far YellowDialog(int a, int b);
extern int far mySoundIsDone(void);
extern void far myDelay(unsigned long ticks);
extern void far EditMessage(long position, int a, int b, int mode);

void far EatMyFood(int mode)
{
    int surplus;

    switch (mode) { case 0: { myBeginSound(0x2c, 0, 0x7e); SetDefaultWindPrompt(1); } break; case 1: { YellowDialog(0x2396, -1); EditMsgDelay = 0; MeHealthCntDwn = 0; EditMessage(WindPromptStrs->pos0, 0x78, 0, 0); } break; case 2: { EditMessage(WindPromptStrs->pos1, 0x78, 0, 0); } break; case 3: { myBeginSound(0x2c, 0, 0x7e); while (!mySoundIsDone()) myDelay(5); myBeginSound(0xa, 0, 0x7e); EditMsgDelay = 0; MeHealthCntDwn = 0; EditMessage(WindPromptStrs->pos2, 0xb4, 0, 0); } break; default: break; }

    if (mode != 2) {
        if (MeHealth + 100 > 100 && mode != 1) {
            if (BpopT - 1 > 0) {
                HealthB += MeHealth / (BpopT - 1);
                if (HealthB > 100)
                    HealthB = 100;
            }
        }
        MeHealth = 100;
        MeHealthCntDwn = 0;
        if (MeWarnHealth < 100) {
            MeWantFood = 0;
            return;
        }
        MeWantFood = 1;
        return;
    }

    surplus = MeHealth;
    if (surplus > 10) {
        surplus -= 10;
        if (NeverHungry != 0)
            surplus = 100;
        if (surplus > 0)
            MeHealthCntDwn = 0;
        if (surplus > 100)
            surplus = 100;
        if (surplus < 0)
            surplus = 0;
        if (MeWarnHealth < surplus && surplus >= 10) {
            MeHealth = surplus;
            MeWantFood = 0;
            return;
        }
    }
    MeHealth = surplus;
    MeWantFood = 1;
}
