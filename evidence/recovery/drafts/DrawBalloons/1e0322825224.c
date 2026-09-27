/* Render the first queued balloon that intersects the current edit view. */
struct MapPoint { int x; int y; };
struct WinRect { int left; int top; int right; int bottom; };
struct BalloonBitmap {
    unsigned char prefix[2];
    unsigned char flags;
    unsigned char reserved[5];
    int width;
    int height;
};

extern unsigned char far * near theEditBufPtr;
extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int near tileWidth;
extern int near tileHeight;
extern unsigned char near displayType;
extern int near win_hwnd[];
extern int far CurBalloonCnt;
extern char far * far CurBalloonMsgs[];
extern int far CurBalloonPlane[];
extern struct MapPoint far CurBalloonPnts[];
extern int far editBufInvalidFlag[];
extern struct MapPoint far MapPnt;
extern struct WinRect far editTileRect;

extern void far font_SetFont(int font);
extern unsigned int far MakeBalloon(char far *message, int flags);
extern void far * far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(unsigned int handle);
extern void far ConvertMaskBitmap2(void far *destination, void far *source,
                                   int destinationHeight, int destinationWidth,
                                   int sourceHeight, int sourceWidth,
                                   int x, int y);
extern void far CopyMaskBitmap2(void far *destination, void far *source,
                                int destinationHeight, int destinationWidth,
                                int sourceHeight, int sourceWidth,
                                int x, int y);
extern void far CopyMonoMaskBitmap(void far *destination, void far *source,
                                   int destinationHeight, int destinationWidth,
                                   int sourceHeight, int sourceWidth,
                                   int x, int y);
extern int far pascal InvalidateRect(int window, struct WinRect far *rect,
                                     int erase);

void far DrawBalloons(void)
{
    unsigned int index;
    unsigned int count;
    unsigned int handle;
    int plane;
    int pixelX;
    int pixelY;
    int tileX;
    int tileY;
    int found;
    int left;
    int top;
    int width;
    int height;
    int destinationWidth;
    int destinationHeight;
    int firstColumn;
    int lastColumn;
    int firstRow;
    int lastRow;
    int row;
    int column;
    unsigned int tileIndex;
    char far *message;
    unsigned char far *editBuffer;
    unsigned char far *bitmapBits;
    struct BalloonBitmap far *bitmap;
    struct WinRect dirty;

    editBuffer = theEditBufPtr;
    font_SetFont(2);
    found = 0;
    count = CurBalloonCnt;
    index = 0;

    while (index < count && !found) {
        message = CurBalloonMsgs[index];
        if (message != 0) {
            plane = CurBalloonPlane[index];
            pixelX = CurBalloonPnts[index].x;
            pixelY = CurBalloonPnts[index].y;
            tileX = pixelX / tileWidth;
            tileY = pixelY / tileHeight;

            if (plane == MapPlane &&
                tileX >= MapPnt.x && tileX < MapPnt.x + editWidth &&
                tileY - 3 >= MapPnt.y && tileY < MapPnt.y + editHeight) {
                found = 1;
                handle = MakeBalloon(message, 0);
                bitmap = (struct BalloonBitmap far *)mem_Lock(handle);
                width = bitmap->width;
                height = bitmap->height;
                left = pixelX + 4;
                top = pixelY - (height + 4);
                bitmapBits = (unsigned char far *)bitmap + 0x0c;
                destinationWidth = tileWidth * editWidth;
                destinationHeight = tileHeight * editHeight;

                if (displayType & 1) {
                    CopyMonoMaskBitmap(editBuffer, bitmapBits,
                                       destinationHeight, destinationWidth,
                                       height, width, left,
                                       destinationHeight - pixelY + 4);
                } else if (bitmap->flags & 0x80) {
                    CopyMaskBitmap2(editBuffer, bitmapBits,
                                    destinationHeight, destinationWidth,
                                    height, width, left,
                                    destinationHeight - pixelY + 4);
                } else {
                    ConvertMaskBitmap2(editBuffer, bitmapBits,
                                       destinationHeight, destinationWidth,
                                       height, width, left,
                                       destinationHeight - pixelY + 4);
                }

                dirty.left = editTileRect.left + left;
                dirty.top = editTileRect.top + top;
                dirty.right = dirty.left + width;
                dirty.bottom = dirty.top + height;
                InvalidateRect(win_hwnd[0], &dirty, 0);

                firstColumn = left / tileWidth;
                lastColumn = (left + width + tileWidth - 1) / tileWidth;
                firstRow = top / tileHeight;
                lastRow = (top + height + tileHeight - 1) / tileHeight;
                row = firstRow;
                while (row < lastRow && row < editHeight) {
                    column = firstColumn;
                    if (column < 0)
                        column = 0;
                    while (column < lastColumn && column < editWidth) {
                        if (row >= 0) {
                            tileIndex = row * editWidth + column;
                            editBufInvalidFlag[tileIndex] = 0xffff;
                        }
                        ++column;
                    }
                    ++row;
                }

                mem_Unlock(handle);
                mem_Free(handle);
            }
        }
        ++index;
    }

    font_SetFont(0);
}
