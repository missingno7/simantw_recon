/*
 * DoTroph: the third argument is a direction-table index.  Dx8[index] and
 * Dy8[index] (two far byte tables in the same segment: MAPSYM _Dx8 at +0,
 * _Dy8 at +8, each with its own selector word BF70/BF72) offset the two
 * supplied coordinates; the adjusted pair determines a direction, then
 * drives MoveMyLife before the edit redraw and one food action.
 *
 * Binding: the original reads es:[bx+8] through the second selector word,
 * i.e. Dy8[index] (the symbol already carries the +8), not Dy8[index + 8].
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
    newY = Dy8[index] + y;
    MoveMyLife(MePlane, newX, newY, MeType,
               GetDir(newX, newY, x, y) - 1);
    DoEditUpdateDraw();
    EatMyFood(1);
}
