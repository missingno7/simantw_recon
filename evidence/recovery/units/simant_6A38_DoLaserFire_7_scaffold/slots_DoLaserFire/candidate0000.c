/*
 * _DoLaserFire hypothesis from its closed target body and named selector
 * operands: play the laser sound, draw two diagonal strokes plus a small
 * colored center block around four supplied screen/map coordinates, and
 * invalidate the affected bounds in the editor window and, when open, the
 * minimap window.  MapPnt/editTileRect and mapXsize/mapYsize/mapTileRect are
 * the exact segment-9 MAPSYM bindings from the local ES selector observations.
 */
struct WinRect { int left; int top; int right; int bottom; };
struct MapPoint { int x; int y; };
extern int near MapPlane;
extern unsigned char near displayType;
extern int near tileWidth;
extern int near tileHeight;
extern int near win_hwnd[];
extern struct MapPoint far MapPnt;
extern struct WinRect far editTileRect;
extern int far mapXsize;
extern int far mapYsize;
extern struct WinRect far mapTileRect;
extern void far myBeginSound(unsigned int first, unsigned int second,
                             unsigned int third);
extern void far clip_Push(void);
extern void far clip_Pop(void);
extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern int far ConvColor(int color);
extern void far GLine(int x1, int y1, int x2, int y2, int color);
extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);
extern void far pascal InvalidateRect(int window, struct WinRect far *rect,
                                      int erase);

void far DoLaserFire(int x1, int y1, int x2, int y2)
{
    int sx, sy, ex, ey;
    int originX, originY;
    struct WinRect dirty;
    struct WinRect dirtyMap;

    myBeginSound(0x37, 0x8265, 0x3f);

    if (MapPlane == 1) {
        if (displayType == 2) {
            x2 = (3 * x2) / 4;
            y2 = (3 * y2) / 4;
            x1 = (3 * x1) / 4;
            y1 = (3 * y1) / 4;
        }

        clip_Push();
        if (win_IsWinOpen(0)) {
            MSClipStart(win_hwnd[0]);
            originX = MapPnt.x * tileWidth - editTileRect.left;
            originX = -originX;
            originY = MapPnt.y * tileHeight - editTileRect.top;
            originY = -originY;
            ex = originX + x1;
            ey = originY + y1;
            sx = originX + x2;
            sy = originY + y2;
            GLine(ex, ey, sx, sy, ConvColor(3));
            GLine(ex + 1, ey + 1, sx + 1, sy + 1, ConvColor(3));
            GBoxFill(sx, sy, sx + 2, sy + 2, ConvColor(2));
        MSClipEnd();

        dirty.left = sx < ex ? sx : ex;
        dirty.top = sy < ey ? sy : ey;
        dirty.right = (sx > ex ? sx : ex) + 2;
        dirty.bottom = (sy > ey ? sy : ey) + 2;
        InvalidateRect(win_hwnd[0], &dirty, 0);
        }

        if (win_IsWinOpen(0x100)) {
            MSClipStart(win_hwnd[1]);
            sx = (x2 / tileWidth) * mapXsize + mapTileRect.left;
            sy = (y2 / tileHeight) * mapYsize + mapTileRect.top;
            ex = (x1 / tileWidth) * mapXsize + mapTileRect.left;
            ey = (y1 / tileHeight) * mapYsize + mapTileRect.top;
            GLine(ex, ey, sx, sy, ConvColor(3));
            GLine(ex + 1, ey + 1, sx + 1, sy + 1, ConvColor(3));
            GBoxFill(sx, sy, sx + 2, sy + 2, ConvColor(1) | 0x20);
            MSClipEnd();

            dirtyMap.left = sx < ex ? sx : ex;
            dirtyMap.top = sy < ey ? sy : ey;
            dirtyMap.right = (sx > ex ? sx : ex) + 2;
            dirtyMap.bottom = (sy > ey ? sy : ey) + 2;
            InvalidateRect(win_hwnd[1], &dirtyMap, 0);
        }
        clip_Pop();
    }
}
