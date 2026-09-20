/*
 * Hypothesis: TileIsVisible accepts a map plane and tile position, and
 * returns one only when the plane agrees with MapPlane and the position lies
 * in the half-open edit rectangle.  The rectangle's left and top words live
 * in the shared far match_position segment at offsets 0x7d2e and 0x7d30;
 * editWidth and editHeight are ordinary DGROUP words.  The strict upper
 * bounds explain the target's <= rejection branches.
 */
struct TileViewport {
    unsigned char unused[0x7d2e];
    int left;
    int top;
};

extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern struct TileViewport far match_position;

int TileIsVisible(int plane, int x, int y)
{
    if (plane != MapPlane)
        return 0;
    if (match_position.left > x)
        return 0;
    if (match_position.left + editWidth <= x)
        return 0;
    if (match_position.top > y)
        return 0;
    if (match_position.top + editHeight <= y)
        return 0;
    return 1;
}
