/*
 * EggBalloons: note an egg laid at (x, y) on a plane.  Nothing happens
 * while an egg balloon is still counting down.  The cell must be visible
 * in the edit view: on the shown MapPlane, within editWidth columns of
 * the map point and within editHeight rows starting three rows above
 * it.  A repeat of the current egg point on the same plane restarts the
 * balloon count; otherwise the point and plane are recorded as the last
 * egg point for the balloon logic.
 */
struct MapPoint {
    int x;
    int y;
};

extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int far EggBalloonCnt;
extern struct MapPoint far MapPnt;
extern struct MapPoint far CurEggPnt;
extern int far CurEggPlane;
extern struct MapPoint far LastEggPnt;
extern int far LastEggPlane;

void far EggBalloons(int x, int y, int plane)
{
    int visible;

    if (EggBalloonCnt != 0)
        return;
    visible = MapPlane == plane && MapPnt.x <= x && x < MapPnt.x + editWidth && MapPnt.y <= y - 3 && y < MapPnt.y + editHeight;
    if (!visible)
        return;
    if (CurEggPnt.x == x && CurEggPnt.y == y && CurEggPlane == plane) {
        EggBalloonCnt++;
        return;
    }
    LastEggPnt.x = x;
    LastEggPnt.y = y;
    LastEggPlane = plane;
}
