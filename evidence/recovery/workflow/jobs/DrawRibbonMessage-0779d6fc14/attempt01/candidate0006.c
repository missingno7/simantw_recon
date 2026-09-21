/*
 * DrawRibbonMessage: refresh the ribbon message object (0x221f) inside
 * the ribbon window clip (win_hwnd[34]).  When the tick count has passed
 * mapMessageRemoveTime both the edit and map message words (DGROUP,
 * addressed through selector slots) are cleared and the object is filled
 * with colour 12; otherwise a pending map message is printed at the
 * object in font 2 (font 0 restored) and an empty one fills the object.
 */
extern int near win_hwnd[];
extern long far editMessage;
extern long far mapMessage;
extern long far mapMessageRemoveTime;

extern void far MSClipStart(int window);
extern unsigned long far TickCount(void);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, long message);
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern void far MSClipEnd(void);

void far DrawRibbonMessage(void)
{
    MSClipStart(win_hwnd[34]);
    if (TickCount() > mapMessageRemoveTime) {
        editMessage = 0L;
        mapMessage = 0L;
        win_FillObjRect(0x221f, ConvColor(12));
    } else if (mapMessage != 0L) {
        font_SetFont(2);
        win_PrintfAtObj(0x221f, mapMessage);
        font_SetFont(0);
    } else {
        win_FillObjRect(0x221f, ConvColor(12));
    }
    MSClipEnd();
}
