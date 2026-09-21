/*
 * InitYelloAnt: (re)spawn the player's yellow ant. MeBase is reset to zero
 * and MeEggCarried is set to the "not carrying" sentinel 0xfd unconditionally.
 * Any active alarm-drop marker (MeDropAlarm) is quietly cleared, the edit
 * layer selection (ELayerMode) is reset to "none" (-1), and the ant's
 * health is filled to 100.
 *
 * The spawn location depends on CurGameType:
 *   - type 3 (tutorial): force plane 1, color 0, mode 2, and a fixed
 *     nest-entrance location (0x40, 0x20), type 0x10 (yellow worker).
 *   - otherwise: color and mode are cleared; if this is not type 2 or the
 *     ant already has a started nest (MeNestStarted != 0), it is reborn at
 *     the saved reincarnation spot (RebornX, RebornY) on plane 2. Else a
 *     free surface tile is hunted: up to 100 random (row, col) picks
 *     (row via SRand16()-SRand16()+0x20, col via SRand8()-SRand8()+0x20)
 *     are tested against MapA until an open tile (< 0x10) is found or the
 *     search times out, keeping the default (0x40, 0x20); the ant is then
 *     placed there on plane 1 as a yellow worker (type 0x40).
 *   In both non-tutorial cases SetMyLife is called with facing dir 2 and
 *   entering code 0xff.
 * Finally ResetYellowVars(MePlane, MeLocX, MeLocY) reinitialises the rest
 * of the yellow-ant movement state from the plane/position that either
 * branch above just established.
 *
 * Profile evidence: simtwo:5AB0 unit context, profile "og" (/Oeglw). The
 * target only writes the MePlane/MeColor/MeMode/MeLocX/MeLocY/MeType tuple
 * once, physically placed after both SetMyLife branches; the SetMyLife
 * branches jump straight past it into the shared ResetYellowVars tail. An
 * if(type==3){...}else{...} shape (tested first) instead ends up compiling
 * that tuple inline right after the branch test, duplicating nothing but
 * placing the block earlier than the target and diverging every offset
 * after it. Testing type!=3 first, with the SetMyLife branches ending in
 * an explicit goto past the tuple, matches the target's physical layout.
 */
extern int near MeBase;
extern int near ELayerMode;
extern int near MeColor;
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int far MeEggCarried;
extern int far MeDropAlarm;
extern int far CurGameType;
extern int far MeMode;
extern int far MeNestStarted;
extern int far RebornX;
extern int far RebornY;
extern unsigned char near MapA[128][64];

extern void far SetMyHealth(int health);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern int far SRand16(void);
extern int far SRand8(void);
extern void far ResetYellowVars(int plane, int x, int y);

void far InitYelloAnt(void)
{
    volatile int type;

    MeBase = 0;
    MeEggCarried = 0xfd;
    if (MeDropAlarm != 0)
        MeDropAlarm = 0;
    ELayerMode = -1;
    SetMyHealth(100);

    type = CurGameType;
    if (type != 3) {
        MeColor = 0;
        MeMode = 0;
        if (type != 2 || MeNestStarted != 0) {
            SetMyLife(2, RebornX, RebornY, 0x10, 2, 0xff);
        } else {
            int x, y;

            x = 0x40;
            y = 0x20;
            {
                int col, count, tries;

                for (tries = 0; tries < 100; tries++) {
                    count = SRand16() - SRand16() + 0x20;
                    col = SRand8() - SRand8() + 0x20;
                    if (MapA[count][col] < 0x10) {
                        x = count;
                        y = col;
                        break;
                    }
                }
            }
            SetMyLife(1, x, y, 0x40, 2, 0xff);
        }
        goto done;
    }
    MePlane = 1;
    MeColor = 0;
    MeMode = 2;
    MeLocX = 0x40;
    MeLocY = 0x20;
    MeType = 0x10;

done:
    ResetYellowVars(MePlane, MeLocX, MeLocY);
}
