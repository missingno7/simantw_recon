struct BalloonPoint {
    int x;
    int y;
};

extern int near MapPlane;
extern struct MapPoint far MapPnt;
extern int near editWidth;
extern int near editHeight;

int BalloonIsVisible(int plane, int x, int y)
{
    if (plane != MapPlane)
        return 0;
    if (x < MapPnt.x || x >= MapPnt.x + editWidth)
        return 0;
    if (y - 3 < MapPnt.y || y >= MapPnt.y + editHeight)
        return 0;
    return 1;
}
