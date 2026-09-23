/* Diagnostic body-shape probes only; no production job or recipe is changed. */
#define MODE_INDEX (LayDownQueenMode <= 0)
extern void clip_Push(void);
extern void clip_Pop(void);
extern int far win_IsWinOpen(int window);
extern void clip_SetWin(int window);
extern void far win_SetGroupSelectedObj(int group, int state, int object);
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
        index = MODE_INDEX;
        win_SetGroupSelectedObj(0x2300, 3, layQueenGroupObjects[index]);
    } else {
        if (win_IsWinOpen(0x1900))
            clip_SetWin(0x1900);
        index = MODE_INDEX;
        win_MakeObjSelected(layQueenObjects[index]);
    }
    clip_Pop();
}
