/* CenterEdit and its unnamed same-object fixed-point scroller.
   The scroller walks the dominant map axis and advances the minor axis when
   the 16.16 error accumulator crosses one cell. */
struct MapPoint { int x; int y; };

extern int near editWidth;
extern int near editHeight;
extern int near MapPlane;
extern struct MapPoint far MapPnt;
static int near ScrollEditBy(int dx, int dy);

int far CenterEdit(int x, int y)
{
    int width;
    int height;
    int result;

    if (ScrollEditBy(x - MapPnt.x - editWidth / 2,
                     y - MapPnt.y - editHeight / 2)) {
        height = 64;
        switch (MapPlane) {
        case 0:
        case 1:
            width = 128;
            break;
        }
        if (MapPnt.x < 0)
            MapPnt.x = 0;
        else if (MapPnt.x + editWidth > width)
            MapPnt.x = width - editWidth;
        if (MapPnt.y < 0)
            MapPnt.y = 0;
        else if (MapPnt.y + editHeight > height)
            MapPnt.y = height - editHeight;
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

static int near ScrollEditBy(int dx, int dy)
{
    int xStep;
    int yStep;
    register int i;
    unsigned long fraction;
    unsigned long error;

    if (dx == 0 && dy == dx)
        return 0;

    xStep = 1;
    yStep = 1;
    if (dx < 0) {
        xStep = -1;
        dx = -dx;
    }
    if (dy < 0) {
        yStep = -1;
        dy = -dy;
    }

    error = 0UL;
    if (dy >= dx) {
        fraction = ((unsigned long)dx << 16) / (unsigned long)dy;
        if (dy > 0) {
            for (i = dy; i > 0; --i) {
                MapPnt.y += yStep;
                error += fraction;
                if ((error >> 16) & 1UL) {
                    MapPnt.x += xStep;
                    error ^= 0x10000UL;
                }
            }
        }
    } else {
        fraction = ((unsigned long)dy << 16) / (unsigned long)dx;
        if (dx > 0) {
            for (i = dx; i > 0; --i) {
                MapPnt.x += xStep;
                error += fraction;
                if ((error >> 16) & 1UL) {
                    MapPnt.y += yStep;
                    error ^= 0x10000UL;
                }
            }
        }
    }
    return 1;
}
