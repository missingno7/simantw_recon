/*
 * Hypothesis: TileIsVisible accepts a map plane and tile position, and
 * returns one only when the plane agrees with MapPlane and the position lies
 * in the half-open edit rectangle.  The rectangle's left and top words live
 * in the shared far match_position segment at offsets 0x7d2e and 0x7d30;
 * editWidth and editHeight are ordinary DGROUP words.  The strict upper
 * bounds explain the target's <= rejection branches.
 */
extern volatile int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern unsigned char far match_position[];
typedef int __based(match_position) *MatchWordPtr;

int TileIsVisible(int plane, int x, int y)
{
    int visible;
    MatchWordPtr left;
    MatchWordPtr top;

    visible = 0;
    left = (MatchWordPtr)0x7d2e;
    top = (MatchWordPtr)0x7d30;
    if (plane == MapPlane &&
        *left <= x &&
        *left + editWidth > x &&
        *top <= y &&
        *top + editHeight > y)
        visible = 1;
    return visible;
}
