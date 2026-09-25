/*
 * Hypothesis: keyboard modifiers choose the yellow-ant action.  With both
 * modifiers held, compare the object rectangle midpoint with the supplied
 * far record's word at offset 8 and select the AddSomeAnts kind.
 */
struct YellowRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int far pascal GetAsyncKeyState(unsigned int key);
extern void far win_GetObjRect(int object, void far *rect);
extern void far AddSomeAnts(int kind);
extern void far AddFood(int food, int count);
extern void far GotoMyAnt(void);

void far MapToYellowAnt(int far *area)
{
    struct YellowRect rect;
    int kind;

    if (GetAsyncKeyState(0x11) & 0x8000) {
        if (GetAsyncKeyState(0x10) & 0x8000) {
            win_GetObjRect(0x110, &rect);
            if ((rect.right + rect.left) / 2 <= area[4])
                kind = 0;
            else
                kind = 1;
            AddSomeAnts(kind);
        } else {
            AddFood(0x96, 1);
        }
    } else {
        GotoMyAnt();
    }
}
