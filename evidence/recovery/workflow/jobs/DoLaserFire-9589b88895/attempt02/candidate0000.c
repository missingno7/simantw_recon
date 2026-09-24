/*
 * _DoLaserFire reissue hypothesis, backed by the closed packet and the
 * SpiderScan call.  The four parameters are screen-pixel endpoints.  On
 * MapPlane 1, draw the same two-line/center-fill mark in the editor window
 * and (if open) the minimap.  The target has separate four-word screen and
 * minimap RECT ranges, and the screen drawing plus its invalidation are
 * guarded by win_IsWinOpen(0).  The segment-9 names below follow the packet's
 * selector bindings for MapPnt, editTileRect, mapXsize, mapYsize/mapTileRect.
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
extern int far pascal InvalidateRect(int window, struct WinRect far *rect,
                                     int erase);

void far DoLaserFire(int x1, int y1, int x2, int y2)
{
    int leftX, topY;
    struct WinRect screenRect;
    struct WinRect mapRect;

    myBeginSound(0x37, 0x8265, 0x3f);
    if (MapPlane == 1) {
        if (displayType == 2) {
            x1 = (3 * x1 + (x1 < 0 ? 3 : 0)) >> 2;
            y1 = (3 * y1 + (y1 < 0 ? 3 : 0)) >> 2;
            x2 = (3 * x2 + (x2 < 0 ? 3 : 0)) >> 2;
            y2 = (3 * y2 + (y2 < 0 ? 3 : 0)) >> 2;
        }

        clip_Push();
        if (win_IsWinOpen(0)) {
            MSClipStart(win_hwnd[0]);
            leftX = editTileRect.left - MapPnt.x * tileWidth + x1;
            topY = editTileRect.top - MapPnt.y * tileHeight + y1;
            GLine(leftX, topY,
                  editTileRect.left - MapPnt.x * tileWidth + x2,
                  editTileRect.top - MapPnt.y * tileHeight + y2,
                  ConvColor(3));
            GLine(leftX + 1, topY + 1,
                  editTileRect.left - MapPnt.x * tileWidth + x2 + 1,
                  editTileRect.top - MapPnt.y * tileHeight + y2 + 1,
                  ConvColor(3));
            GBoxFill(leftX, topY, leftX + 2, topY + 2, ConvColor(2));
            MSClipEnd();

            screenRect.left = leftX < editTileRect.left - MapPnt.x * tileWidth + x2
                            ? leftX : editTileRect.left - MapPnt.x * tileWidth + x2;
            screenRect.top = topY < editTileRect.top - MapPnt.y * tileHeight + y2
                           ? topY : editTileRect.top - MapPnt.y * tileHeight + y2;
            screenRect.right = (leftX > editTileRect.left - MapPnt.x * tileWidth + x2
                              ? leftX : editTileRect.left - MapPnt.x * tileWidth + x2) + 2;
            screenRect.bottom = (topY > editTileRect.top - MapPnt.y * tileHeight + y2
                               ? topY : editTileRect.top - MapPnt.y * tileHeight + y2) + 2;
            InvalidateRect(win_hwnd[0], &screenRect, 0);
        }

        if (win_IsWinOpen(0x100)) {
            MSClipStart(win_hwnd[1]);
            leftX = (x1 / tileWidth) * mapXsize + mapTileRect.left;
            topY = (y1 / tileHeight) * mapYsize + mapTileRect.top;
            GLine(leftX, topY,
                  (x2 / tileWidth) * mapXsize + mapTileRect.left,
                  (y2 / tileHeight) * mapYsize + mapTileRect.top,
                  ConvColor(3));
            GLine(leftX + 1, topY + 1,
                  (x2 / tileWidth) * mapXsize + mapTileRect.left + 1,
                  (y2 / tileHeight) * mapYsize + mapTileRect.top + 1,
                  ConvColor(3));
            GBoxFill(leftX, topY, leftX + 2, topY + 2,
                     ConvColor(1) | 0x20);
            MSClipEnd();

            mapRect.left = leftX < (x2 / tileWidth) * mapXsize + mapTileRect.left
                         ? leftX : (x2 / tileWidth) * mapXsize + mapTileRect.left;
            mapRect.top = topY < (y2 / tileHeight) * mapYsize + mapTileRect.top
                        ? topY : (y2 / tileHeight) * mapYsize + mapTileRect.top;
            mapRect.right = (leftX > (x2 / tileWidth) * mapXsize + mapTileRect.left
                           ? leftX : (x2 / tileWidth) * mapXsize + mapTileRect.left) + 2;
            mapRect.bottom = (topY > (y2 / tileHeight) * mapYsize + mapTileRect.top
                            ? topY : (y2 / tileHeight) * mapYsize + mapTileRect.top) + 2;
            InvalidateRect(win_hwnd[1], &mapRect, 0);
        }
        clip_Pop();
    }
}
