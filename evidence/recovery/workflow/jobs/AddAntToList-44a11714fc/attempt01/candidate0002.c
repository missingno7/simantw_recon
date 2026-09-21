/*
 * AddAntToList: add an ant to the list for its plane when that list has
 * room: planes 0 and 1 use the A list (up to 1000 entries), plane 2 the
 * B list and any other plane the R list (500 each).  When the ant was
 * added its life cell is set for the plane and 1 is returned, otherwise
 * 0.
 */
extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;

extern void far AddAntToAList(int x, int y, int type, int a, int b);
extern void far AddAntToBList(int x, int y, int type, int a, int b);
extern void far AddAntToRList(int x, int y, int type, int a, int b);
extern void far SetLife(int plane, int x, int y, int type);

int far AddAntToList(int plane, int x, int y, int type, int a, int b)
{
    int added;

    added = 0;
    if (plane <= 1) {
        if (ListIndexA < 1000) {
            AddAntToAList(x, y, type, a, b);
            added = 1;
        }
    } else if (plane == 2) {
        if (ListIndexB < 500) {
            AddAntToBList(x, y, type, a, b);
            added = 1;
        }
    } else if (ListIndexR < 500) {
        AddAntToRList(x, y, type, a, b);
        added = 1;
    }
    if (added != 0)
        SetLife(plane, x, y, type);
    return added;
}
