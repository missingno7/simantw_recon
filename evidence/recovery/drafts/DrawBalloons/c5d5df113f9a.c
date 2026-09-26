/* _DrawBalloons: walk the active balloon records, create each balloon bitmap,
   clip it to the edit viewport, invalidate the affected rectangle, then free it. */
struct Rect { int left, top, right, bottom; };
struct BitmapHeader { unsigned long size; int width, height; unsigned planes, bits; };
extern unsigned char far * near theEditBufPtr;
extern int near tileWidth, tileHeight, MapPlane, editWidth, editHeight;
extern unsigned char near displayType;
extern int near win_hwnd[];
extern int far match_position[];
extern int far match_length[];
extern int far CurBalloonPlane[];
extern int far CurBalloonPnts[];
extern struct Rect far editTileRect;
extern void far font_SetFont(int font);
extern unsigned int far MakeBalloon(void far *source, int flags);
extern void far * far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern void far ConvertMaskBitmap2(void far *editBuffer, void far *bitmap,
                                   int x, int y, int sourceWidth, int sourceHeight,
                                   int destWidth, int destHeight, int left, int top);
extern void far CopyMaskBitmap2(void far *editBuffer, void far *bitmap,
                                 int x, int y, int sourceWidth, int sourceHeight,
                                 int destWidth, int destHeight, int left, int top);
extern void far CopyMonoMaskBitmap(void far *editBuffer, void far *bitmap,
                                    int x, int y, int sourceWidth, int sourceHeight,
                                    int destWidth, int destHeight, int left, int top);
extern int far pascal InvalidateRect(int window, struct Rect far *rect, int erase);

void far DrawBalloons(void)
{
    unsigned i;
    unsigned count;
    unsigned handle;
    int plane, tileX, tileY, x, y, width, height;
    int left, top, right, bottom;
    void far *bitmap;
    void far *source;
    struct Rect dirty;
    void far *editBuffer;

    editBuffer = theEditBufPtr;
    font_SetFont(2);
    count = 0;
    while (count < 500) {
        if (CurBalloonPlane[count] == 0)
            break;
        for (i = 0; i < 2; ++i) {
            plane = CurBalloonPlane[count];
            tileX = CurBalloonPnts[count * 2];
            tileY = CurBalloonPnts[count * 2 + 1];
            x = tileX / tileWidth;
            y = tileY / tileHeight;
            if (plane == MapPlane && x >= match_position[count] &&
                x < match_position[count] + editWidth &&
                y >= match_length[count] - 3 &&
                y < match_length[count] + editHeight) {
                source = (void far *)&CurBalloonPnts[count * 2];
                handle = MakeBalloon(source, 0);
                if (handle) {
                    bitmap = mem_Lock(handle);
                    width = ((struct BitmapHeader far *)bitmap)->width;
                    height = ((struct BitmapHeader far *)bitmap)->height;
                    left = x * tileWidth;
                    top = y * tileHeight;
                    right = left + width;
                    bottom = top + height;
                    if (displayType & 1)
                        ConvertMaskBitmap2(editBuffer, bitmap, left, top,
                                           width, height, editWidth * tileWidth,
                                           editHeight * tileHeight, x, y);
                    else if (((unsigned char far *)bitmap)[2] & 0x80)
                        CopyMaskBitmap2(editBuffer, bitmap, left, top,
                                        width, height, editWidth * tileWidth,
                                        editHeight * tileHeight, x, y);
                    else
                        CopyMonoMaskBitmap(editBuffer, bitmap, left, top,
                                           width, height, editWidth * tileWidth,
                                           editHeight * tileHeight, x, y);
                    dirty.left = left; dirty.top = top;
                    dirty.right = right; dirty.bottom = bottom;
                    InvalidateRect(win_hwnd[25], &dirty, 0);
                    mem_Unlock(handle);
                    mem_Free(handle);
                }
            }
        }
        ++count;
    }
    font_SetFont(0);
    (void)editTileRect;
}
