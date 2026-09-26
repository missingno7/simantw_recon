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
    int xCount;
    int yCount;
    int i;
    long fraction;
    long error;

    if (dx == 0 && dy == 0)
        return 0;

    xStep = dx < 0 ? -1 : 1;
    yStep = dy < 0 ? -1 : 1;
    xCount = dx < 0 ? -dx : dx;
    yCount = dy < 0 ? -dy : dy;
    error = 0L;

    if (yCount >= xCount) {
        fraction = ((long)xCount << 16) / yCount;
        for (i = 0; i < yCount; ++i) {
            MapPnt.y += yStep;
            error += fraction;
            if ((error >> 16) & 1L) {
                MapPnt.x += xStep;
                error ^= 0x10000L;
            }
        }
    } else {
        fraction = ((long)yCount << 16) / xCount;
        for (i = 0; i < xCount; ++i) {
            MapPnt.x += xStep;
            error += fraction;
            if ((error >> 16) & 1L) {
                MapPnt.y += yStep;
                error ^= 0x10000L;
            }
        }
    }
    return 1;
}
