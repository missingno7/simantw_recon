/*
 * Hypothesis: the third argument is a direction-table index.  Its Dx8 and
 * Dy8 entries (the latter at index+8) offset the two supplied coordinates;
 * the adjusted pair determines a direction, then drives MoveMyLife before
 * the edit redraw and one food action.
 */
extern char far Dx8[];
extern char far Dy8[];
extern int near MeType;
extern int near MePlane;
extern int far GetDir(int a, int b, int c, int d);
extern void far MoveMyLife(int plane, int x, int y, int type, int direction);
extern void far DoEditUpdateDraw(void);
extern void far EatMyFood(int amount);

void far DoTroph(int x, int y, int index)
{
    int newX;
    int newY;

    newX = Dx8[index] + x;
    newY = Dy8[index + 8] + y;
    MoveMyLife(MePlane, newX, newY, MeType,
               GetDir(newX, newY, x, y) - 1);
    DoEditUpdateDraw();
    EatMyFood(1);
}
