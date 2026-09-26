/* MapPnt is the MAPSYM object at PACK offset 0x7d2e. */
extern volatile int near MapPlane;
extern int near editWidth;
extern int near editHeight;
struct MapPoint { int x; int y; };
extern struct MapPoint far MapPnt;

int TileIsVisible(int plane, int x, int y)
{
    int visible;
    visible = plane == MapPlane &&
        MapPnt.x <= x && MapPnt.x + editWidth > x &&
        MapPnt.y <= y && MapPnt.y + editHeight > y;
    return visible;
}
