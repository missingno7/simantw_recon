/*
 * Hypothesis: the private redraw flag chooses between selecting the queen
 * group and selecting the queen-mode object.  The object arrays are indexed
 * by (LayDownQueenMode < 1), matching the target's compare/sbb/neg/shift
 * sequence; the far mode object is the named SIMANT data symbol at ES:836e.
 */
extern void clip_Push(void);
extern void clip_Pop(void);
extern int far win_IsWinOpen(int window);
extern void far clip_SetWin(int window);
extern void far win_SetGroupSelectedObj(int object, int state, int group);
extern void far win_MakeObjSelected(int object);

extern int near layQueenModeDisplayFlag;
extern int far LayDownQueenMode;
extern int near layQueenGroupObjects[2];
extern int near layQueenObjects[2];

void far UpdateLayQueenModeDisplay(void)
{
    int index;

    clip_Push();
    if (layQueenModeDisplayFlag) {
        index = LayDownQueenMode == 0;
        win_SetGroupSelectedObj(0x2300, 3, layQueenGroupObjects[index]);
    } else {
        if (win_IsWinOpen(0x1900))
            clip_SetWin(0x1900);
        index = LayDownQueenMode == 0;
        win_MakeObjSelected(layQueenObjects[index]);
    }
    clip_Pop();
}
