/*
 * GotoQueen: scroll the map/edit view onto the first ant whose masked
 * attribute byte (attribute & 0xf8) matches the caste/type key,
 * searching the black list (Dx8[si+0x3d18], 500 entries, plane 2, at
 * BlistX/BlistY), then the ant list (Dx8[si+0x2f62], 1000 entries,
 * plane 1, at AlistX/AlistY), then the red list (Dx8[si+0x46e6], 500
 * entries, plane 3, at RlistX/RlistY).  Nothing happens if no ant
 * matches.  Once found: erase the map cursor inside the map window
 * clip (win_hwnd[1]) if the map window (0x100) is open, then either
 * recentre the edit view in place (CenterEdit, refreshing with
 * UpdateEdit when it reports a change, and clearing UDMapFlip) when
 * already on that ant's plane, or switch to that plane and location
 * (SetMapPlaneLocation) and redraw the map if its window is open.
 * Finally redraw the map cursor inside the clip if the map window is
 * open.  Mirrors the admitted CenterAnt/GotoMapPoint/GotoMyAnt/
 * GotoSpider siblings in this same SIMANT_MODULE object.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) Dx8[];
extern unsigned char far BlistX[];
extern unsigned char far BlistY[];
extern unsigned char far AlistX[];
extern unsigned char far AlistY[];
extern unsigned char far RlistX[];
extern unsigned char far RlistY[];
extern int near win_hwnd[];
extern int near MapPlane;
extern int far UDMapFlip;

extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far EraseMapCursor(void);
extern void far DrawMapCursor(void);
extern int far CenterEdit(int x, int y);
extern void far UpdateEdit(void);
extern void far SetMapPlaneLocation(int plane, int x, int y);
extern void far DrawMap(void);

void far GotoQueen(int type)
{
    int si;
    int x, y, plane;

    for (si = 0; si < 500; si++)
        if ((Dx8[si + 0x3d18] & 0xf8) == type) {
            x = BlistX[si];
            y = BlistY[si];
            if (win_IsWinOpen(0x100)) {
                MSClipStart(win_hwnd[1]);
                EraseMapCursor();
                MSClipEnd();
            }
            plane = 2;
            goto dispatch;
        }
    for (si = 0; si < 1000; si++)
        if ((Dx8[si + 0x2f62] & 0xf8) == type) {
            x = AlistX[si];
            y = AlistY[si];
            if (win_IsWinOpen(0x100)) {
                MSClipStart(win_hwnd[1]);
                EraseMapCursor();
                MSClipEnd();
            }
            plane = 1;
            goto dispatch;
        }
    for (si = 0; si < 500; si++)
        if ((Dx8[si + 0x46e6] & 0xf8) == type) {
            x = RlistX[si];
            y = RlistY[si];
            if (win_IsWinOpen(0x100)) {
                MSClipStart(win_hwnd[1]);
                EraseMapCursor();
                MSClipEnd();
            }
            plane = 3;
            goto dispatch;
        }
    return;

dispatch:
    if (MapPlane == plane) {
        if (CenterEdit(x, y))
            UpdateEdit();
        UDMapFlip = 0;
    } else {
        SetMapPlaneLocation(plane, x, y);
        if (win_IsWinOpen(0x100))
            DrawMap();
    }
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        DrawMapCursor();
        MSClipEnd();
    }
}
