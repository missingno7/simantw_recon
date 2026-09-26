/* Candidate translation unit simant_6A38_DoLaserFire_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoLaserFire
 * SCAFFOLDED: unclaimed members _processEdit are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

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

extern int far match_position;  /* scaffold reference for pool word BF0A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MeMode;  /* scaffold reference for pool word BF0C (segment 9, MAPSYM_SITE_NAME) */
extern int far match_length;  /* scaffold reference for pool word BF0E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MeCmd;  /* scaffold reference for pool word BF10 (segment 9, MAPSYM_SITE_NAME) */
extern int far pack_buf;  /* scaffold reference for pool word BF12 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word BF14 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word BF16 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word BF18 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MeGoalPlane;  /* scaffold reference for pool word BF1A (segment 9, MAPSYM_SITE_NAME) */
extern int far MeGoalX;  /* scaffold reference for pool word BF1C (segment 9, MAPSYM_SITE_NAME) */
extern int far MeGoalY;  /* scaffold reference for pool word BF1E (segment 9, MAPSYM_SITE_NAME) */
extern int far MeCrazyCnt;  /* scaffold reference for pool word BF20 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeMoveMe;  /* scaffold reference for pool word BF22 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_processEdit(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_processEdit)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _processEdit.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF06 BF08 BF0A BF0C BF0E BF10 BF12 BF14 BF16 BF18 BF1A BF1C BF1E BF20 BF22; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_processEdit(void)
{
    volatile int t;

    t = *(int far *)&editTileRect;
    t = *(int far *)&MapPnt;
    t = match_position;
    t = MeMode;
    t = match_length;
    t = MeCmd;
    t = pack_buf;
    t = Scycle;
    t = EditColumns;
    t = MiscStrs;
    t = MeGoalPlane;
    t = MeGoalX;
    t = MeGoalY;
    t = MeCrazyCnt;
    t = MeMoveMe;
}

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

