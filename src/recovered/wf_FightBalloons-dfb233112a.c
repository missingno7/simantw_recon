/*
 * FightBalloons: note a fight at (x, y) on a plane.  Nothing happens
 * while a fight balloon is still counting down.  The cell must be visible
 * in the edit view: on the shown MapPlane, within editWidth columns of
 * the map point and within editHeight rows starting three rows above
 * it.  A repeat of the current fight point on the same plane restarts the
 * balloon count; otherwise the point and plane are recorded as the last
 * fight point for the balloon logic.
 */
struct MapPoint {
    int x;
    int y;
};

extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int far FightBalloonCnt;
extern struct MapPoint far MapPnt;
extern struct MapPoint far CurFightPnt;
extern int far CurFightPlane;
extern struct MapPoint far LastFightPnt;
extern int far LastFightPlane;

void far FightBalloons(int x, int y, int plane)
{
    int visible;

    if (FightBalloonCnt != 0)
        return;
    visible = MapPlane == plane && MapPnt.x <= x && x < MapPnt.x + editWidth && MapPnt.y <= y - 3 && y < MapPnt.y + editHeight;
    if (!visible)
        return;
    if (CurFightPnt.x == x && CurFightPnt.y == y && CurFightPlane == plane) {
        FightBalloonCnt++;
        return;
    }
    LastFightPnt.x = x;
    LastFightPnt.y = y;
    LastFightPlane = plane;
}
