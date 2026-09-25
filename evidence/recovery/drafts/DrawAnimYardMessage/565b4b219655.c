/*
 * DrawAnimYardMessage: refresh the yard message object (0x1916) inside
 * the yard window clip (win_hwnd[25]) when that window's handle slot
 * (win_hwnd[35]) is set and window 0x1900 is open.  When the tick count
 * has passed mapMessageRemoveTime both the edit and map message words
 * (DGROUP, addressed through selector slots) are cleared and the object
 * is filled with colour 12; otherwise a pending map message is printed
 * at the object in font 2 (font 0 restored) and an empty one fills the
 * object.  Twin of the accepted DrawRibbonMessage.
 */
extern int near win_hwnd[];
extern long far editMessage;
extern long far mapMessage;
extern long far mapMessageRemoveTime;

extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern long far TickCount(void);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, long message);
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern void far MSClipEnd(void);

void far DrawAnimYardMessage(void)
{
    if (win_hwnd[35] == 0)
        return;
    if (win_IsWinOpen(0x1900) == 0)
        return;
    MSClipStart(win_hwnd[25]);
    if (TickCount() > mapMessageRemoveTime) {
        editMessage = 0L;
        mapMessage = 0L;
        win_FillObjRect(0x1916, ConvColor(12));
    } else if (mapMessage != 0L) {
        font_SetFont(2);
        win_PrintfAtObj(0x1916, mapMessage);
        font_SetFont(0);
    } else {
        win_FillObjRect(0x1916, ConvColor(12));
    }
    MSClipEnd();
}
