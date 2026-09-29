/*
 * QueenBalloons: note a queen event at (x, y) on a plane.  Nothing happens
 * while a queen balloon is still counting down.  The cell must be visible
 * in the edit view: on the shown MapPlane, within editWidth columns of
 * the map point and within editHeight rows starting three rows above
 * it.  A repeat of the current queen point on the same plane restarts the
 * balloon count; otherwise the point and plane are recorded as the last
 * queen point for the balloon logic.
 */
struct MapPoint {
    int x;
    int y;
};

extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int far QueenBalloonCnt;
extern struct MapPoint far MapPnt;
extern struct MapPoint far CurQueenPnt;
extern int far CurQueenPlane;
extern struct MapPoint far LastQueenPnt;
extern int far LastQueenPlane;

void far QueenBalloons(int x, int y, int plane)
{
    int visible;

    if (QueenBalloonCnt != 0)
        return;
    visible = MapPlane == plane && MapPnt.x <= x && x < MapPnt.x + editWidth && MapPnt.y <= y - 3 && y < MapPnt.y + editHeight;
    if (!visible)
        return;
    if (CurQueenPnt.x == x && CurQueenPnt.y == y && CurQueenPlane == plane) {
        QueenBalloonCnt++;
        return;
    }
    LastQueenPnt.x = x;
    LastQueenPnt.y = y;
    LastQueenPlane = plane;
}
