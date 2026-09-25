/*
 * EditMsgBalloon: prepare a message balloon at pixel (x, y) on a map plane.
 * The pixel position is scaled to tiles (>> 4) and offset by the far PACK
 * point MapPnt (verified declaration in BalloonIsVisible), and the balloon
 * is visible only when the plane is the current MapPlane and the tile lies
 * inside the edit view (MapPnt.x .. MapPnt.x + editWidth, MapPnt.y + 3 ..
 * MapPnt.y + editHeight), the same test as BalloonIsVisible.  The result
 * is materialised into a flag; when it holds and the far message pointer
 * (fifth argument, tested as a 32-bit value) is non-null, the two 256-byte
 * text line buffers are emptied.  The remaining balloon layout code is not
 * part of this 114-byte extent; the fourth argument is unused here.
 */
struct BalloonPoint {
    int x;
    int y;
};

extern int near MapPlane;
extern struct BalloonPoint far MapPnt;
extern int near editWidth;
extern int near editHeight;

void far EditMsgBalloon(int x, int y, int plane, int style, char far *msg)
{
    char line1[256];
    char line2[256];
    int tileX;
    int tileY;
    int visible;

    tileX = (x >> 4) + MapPnt.x;
    tileY = (y >> 4) + MapPnt.y;
    visible = (plane == MapPlane &&
               tileX >= MapPnt.x && tileX < MapPnt.x + editWidth &&
               tileY - 3 >= MapPnt.y && tileY < MapPnt.y + editHeight);
    if (visible && msg != 0) {
        line2[0] = 0;
        line1[0] = 0;
    }
}
