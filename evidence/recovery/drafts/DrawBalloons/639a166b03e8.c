/* Render the first queued balloon that intersects the edit viewport. */
struct MapPoint { int x; int y; };
struct WinRect { int left; int top; int right; int bottom; };
struct BalloonBitmap {
    unsigned char prefix[2];
    unsigned char flags;
    unsigned char reserved[5];
    unsigned int width;
    unsigned int height;
};

extern unsigned char far * near theEditBufPtr;
extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int near tileWidth;
extern int near tileHeight;
extern unsigned char near displayType;
extern int near win_hwnd[];
extern int near edata[];
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
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);


void far DrawBalloons(void)
{
  int far * volatile mapXPointer;
  int far * volatile mapYPointer;
  unsigned char far * volatile editBuffer;
  struct BalloonBitmap far * bitmap;
  struct WinRect dirty;
  char far * far *messageSlot;
  int index;
  volatile int planeOffset;
  int pointOffset;
  unsigned int handle;
  int tileIndex;
  int plane;
  struct MapPoint pixel;
  int tileX;
  int tileY;
  int visibleCount;
  int left;
  int top;
  int firstColumn;
  int lastColumn;
  int firstRow;
  int lastRow;
  int row;
  int column;
  int rowOffset;
  int columnCount;
  int rowCount;
  int tileLimit;
  int isVisible;
  editBuffer = theEditBufPtr;
  font_SetFont(2);
  edata[53] = 0x1f4;
  index = (visibleCount = 0);
  if (CurBalloonCnt > 0)
  {
    planeOffset = 0;
    pointOffset = 0;
    mapXPointer = &MapPnt.x;
    mapYPointer = &MapPnt.y;
    do
    {
      if (visibleCount < 1)
      {
      messageSlot = (char far * far *)((char far *)CurBalloonMsgs + pointOffset);
      if (*messageSlot != 0)
      {
        plane = *((int far *)((char far *)CurBalloonPlane + planeOffset));
        pixel = *((struct MapPoint far *)((char far *)CurBalloonPnts + pointOffset));
        tileX = pixel.x / tileWidth;
        tileY = pixel.y / tileHeight;
        isVisible = (plane == MapPlane && tileX >= (*mapXPointer) &&
                     tileX < (*mapXPointer) + editWidth &&
                     tileY - 3 >= (*mapYPointer) &&
                     tileY < (*mapYPointer) + editHeight);
        if (isVisible)
        {
          ++visibleCount;
          handle = MakeBalloon(*messageSlot, 0);
          bitmap = (struct BalloonBitmap far *) mem_Lock(handle);
          left = pixel.x + 4;
          top = pixel.y - (bitmap->height + 4);
          left -= (*mapXPointer) * tileWidth;
          top -= (*mapYPointer) * tileHeight;
          if (displayType & 1)
            goto draw_mono_copy;
          if (bitmap->flags & 0x80)
          {
            CopyMaskBitmap2(editBuffer, ((unsigned char far *)bitmap) + 0x0c, tileHeight * editHeight, tileWidth * editWidth, bitmap->height, bitmap->width, left, tileHeight * editHeight - bitmap->height - top);
          }
          else
          {
            ConvertMaskBitmap2(editBuffer, ((unsigned char far *)bitmap) + 0x0c, tileHeight * editHeight, tileWidth * editWidth, bitmap->height, bitmap->width, left, tileHeight * editHeight - bitmap->height - top);
          }
          goto draw_copy_done;
        draw_mono_copy:
          CopyMonoMaskBitmap(editBuffer, ((unsigned char far *)bitmap) + 0x0c, tileHeight * editHeight, tileWidth * editWidth, bitmap->height, bitmap->width, left, tileHeight * editHeight - bitmap->height - top);
        draw_copy_done:
          ;
          dirty.left = editTileRect.left + left;
          dirty.top = editTileRect.top + top;
          dirty.right = dirty.left + bitmap->width;
          dirty.bottom = dirty.top + bitmap->height;
          InvalidateRect(win_hwnd[0], &dirty, 0);
          firstColumn = left / tileWidth - (*mapXPointer);
          lastColumn = (left + bitmap->width + tileWidth - 1) / tileWidth - (*mapXPointer);
          firstRow = top / tileHeight - (*mapYPointer);
          lastRow = (top + bitmap->height + tileHeight - 1) / tileHeight - (*mapYPointer);
          tileLimit = editWidth * editHeight;
          rowOffset = firstRow * editWidth + firstColumn;
          row = firstRow;
          rowCount = lastRow - firstRow;
          while (rowCount != 0)
          {
            column = firstColumn;
            columnCount = lastColumn - firstColumn;
            tileIndex = rowOffset;
            while (columnCount != 0)
            {
              if (tileIndex >= 0 && tileIndex < tileLimit)
                editBufInvalidFlag[tileIndex] = 0xffff;
              ++column;
              ++tileIndex;
              --columnCount;
            }

            --rowCount;
            if (rowCount == 0)
              break;
            rowOffset += editWidth;
            ++row;
          }

          mem_Unlock(handle);
          mem_Free(handle);
        }
      }
      else
        break;
      planeOffset += 2;
      pointOffset += 4;
      ++index;
      }
    }
    while (index < CurBalloonCnt);
  }
  font_SetFont(0);
  CurBalloonCnt = 0;
}



