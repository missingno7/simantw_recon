/*
 * GotoQueen: scroll the map/edit view onto the first ant whose masked
 * attribute byte (attribute & 0xf8) matches the caste/type key,
 * searching the black list (Dx8[si+0x3d18], 500 entries, plane 2, at
 * Dx8[si+0x3736]/Dx8[si+0x392c] for x/y), then the ant list
 * (Dx8[si+0x2f62], 1000 entries, plane 1, at Dx8[si+0x23a4]/
 * Dx8[si+0x278e]), then the red list (Dx8[si+0x46e6], 500 entries,
 * plane 3, at Dx8[si+0x4104]/Dx8[si+0x42fa]).  Nothing happens if no
 * ant matches.  Once found: erase the map cursor inside the map
 * window clip (win_hwnd[1]) if the map window (0x100) is open, then
 * either recentre the edit view in place (CenterEdit, refreshing with
 * UpdateEdit when it reports a change, and clearing UDMapFlip) when
 * already on that ant's plane, or switch to that plane and location
 * (SetMapPlaneLocation) and redraw the map if its window is open.
 * Finally redraw the map cursor inside the clip if the map window is
 * open.  Mirrors the admitted CenterAnt/GotoMapPoint/GotoMyAnt/
 * GotoSpider siblings in this same SIMANT_MODULE object; the coordinate
 * fields share Dx8's own far selector with the attribute test that
 * found the match, so they are read through Dx8 rather than through
 * separately named arrays that would force a second selector load.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) Dx8[];
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
    int x, y;

    for (si = 0; si < 500; si++)
        if ((Dx8[si + 0x3d18] & 0xf8) == type) {
            x = Dx8[si + 0x3736];
            y = Dx8[si + 0x392c];
            if (win_IsWinOpen(0x100)) {
                MSClipStart(win_hwnd[1]);
                EraseMapCursor();
                MSClipEnd();
            }
            if (MapPlane == 2) {
                if (CenterEdit(x, y))
                    UpdateEdit();
                UDMapFlip = 0;
            } else {
                SetMapPlaneLocation(2, x, y);
                if (win_IsWinOpen(0x100))
                    DrawMap();
            }
            if (win_IsWinOpen(0x100)) {
                MSClipStart(win_hwnd[1]);
                DrawMapCursor();
                MSClipEnd();
            }
            return;
        }
    for (si = 0; si < 1000; si++)
        if ((Dx8[si + 0x2f62] & 0xf8) == type) {
            x = Dx8[si + 0x23a4];
            y = Dx8[si + 0x278e];
            if (win_IsWinOpen(0x100)) {
                MSClipStart(win_hwnd[1]);
                EraseMapCursor();
                MSClipEnd();
            }
            if (MapPlane == 1) {
                if (CenterEdit(x, y))
                    UpdateEdit();
                UDMapFlip = 0;
            } else {
                SetMapPlaneLocation(1, x, y);
                if (win_IsWinOpen(0x100))
                    DrawMap();
            }
            if (win_IsWinOpen(0x100)) {
                MSClipStart(win_hwnd[1]);
                DrawMapCursor();
                MSClipEnd();
            }
            return;
        }
    for (si = 0; si < 500; si++)
        if ((Dx8[si + 0x46e6] & 0xf8) == type) {
            x = Dx8[si + 0x4104];
            y = Dx8[si + 0x42fa];
            if (win_IsWinOpen(0x100)) {
                MSClipStart(win_hwnd[1]);
                EraseMapCursor();
                MSClipEnd();
            }
            if (MapPlane == 3) {
                if (CenterEdit(x, y))
                    UpdateEdit();
                UDMapFlip = 0;
            } else {
                SetMapPlaneLocation(3, x, y);
                if (win_IsWinOpen(0x100))
                    DrawMap();
            }
            if (win_IsWinOpen(0x100)) {
                MSClipStart(win_hwnd[1]);
                DrawMapCursor();
                MSClipEnd();
            }
            return;
        }
}
