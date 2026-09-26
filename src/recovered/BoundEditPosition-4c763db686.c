/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x3e97] -> MapPnt, match_position[0x3e98] -> MapPnt.y (one selector word per symbol in the object).
 *
 * Hypothesis: choose a 64- or 128-pixel horizontal edit bound from MapPlane,
 * clamp the far MapPnt.x coordinate using editWidth, then clamp y to
 * the 64-pixel edit area using editHeight.  Negative y is normalized and
 * returns immediately, matching the target's short second-path return.
 */
extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
struct MapPoint { int x; int y; };
extern struct MapPoint far MapPnt;

void far BoundEditPosition(void)
{
    int limit;
    switch (MapPlane) {
    case 0:
    case 1:
        limit = 0x80;
        break;
    default:
        limit = 0x40;
        break;
    }

    if (MapPnt.x < 0)
        MapPnt.x = 0;
    else if (MapPnt.x + editWidth > limit)
        MapPnt.x = limit - editWidth;

    if (MapPnt.y < 0) {
        MapPnt.y = 0;
        return;
    }
    if (MapPnt.y + editHeight > 0x40)
        MapPnt.y = 0x40 - editHeight;
}
