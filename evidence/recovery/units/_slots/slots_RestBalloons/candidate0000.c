/*
 * RestBalloons: note a resting ant at (x, y) on a plane.  Nothing happens
 * while a rest balloon is still counting down.  The cell must be visible
 * in the edit view: on the shown MapPlane, within editWidth columns of
 * the map point and within editHeight rows starting three rows above
 * it.  A repeat of the current rest point on the same plane restarts the
 * balloon count; otherwise the point and plane are recorded as the last
 * rest point for the balloon logic.
 */
struct MapPoint {
    int x;
    int y;
};

extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int far RestBalloonCnt;
extern struct MapPoint far MapPnt;
extern struct MapPoint far CurRestPnt;
extern int far CurRestPlane;
extern struct MapPoint far LastRestPnt;
extern int far LastRestPlane;

void far RestBalloons(int x, int y, int plane)
{
    int visible;

    if (RestBalloonCnt != 0)
        return;
    visible = MapPlane == plane && MapPnt.x <= x && x < MapPnt.x + editWidth && MapPnt.y <= y - 3 && y < MapPnt.y + editHeight;
    if (!visible)
        return;
    if (CurRestPnt.x == x && CurRestPnt.y == y && CurRestPlane == plane) {
        RestBalloonCnt++;
        return;
    }
    LastRestPnt.x = x;
    LastRestPnt.y = y;
    LastRestPlane = plane;
}
