/* Measure a picture and its strings, center a modal window, and handle its events. */
struct WinRect { int left; int top; int right; int bottom; };
struct BitmapSize { int width; int height; };
struct DialogEvent { unsigned char pad[12]; int object; unsigned char tail[2]; };
extern int near win_hwnd[];
extern int near rootWnd;
static char far * far *pictureLines;
static int near pictureLineCount;
static unsigned int near pictureBitmap;
extern int far font_FontHeight(void);
extern int far font_StringWidth(char far *string);
extern void far font_SetFont(int font);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far win_LockWin(int window);
extern void far win_UnlockWin(int window);
extern void far win_Open(int window, int left, int top, int right, int bottom);
extern void far win_Close(int window);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern int far win_GetEvent(struct DialogEvent far *event);
extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);
extern void far win_MakeObjSelectable(int object);
extern void far win_FlushEvents(void);
extern void far DialogWaitInit(int mode);
extern int near DialogAbortOrCont(void);
extern void near DialogDone(void);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern int far win_IsWinInFront(int window);
extern int far pascal GetClientRect(unsigned int window, struct WinRect far *rect);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far win_DrawWindow(int window);
extern int far pascal IsWindowVisible(unsigned int window);
extern int far pascal GetAsyncKeyState(unsigned int key);
extern int far pascal MessageBeep(unsigned int type);
extern int far font_FontHeight(void);

void far PictureDialog(char far * far *strings, int count, int picture, int force)
{
    struct BitmapSize size;
    struct WinRect client;
    struct WinRect rect;
    struct DialogEvent event;
    int height;
    int pictureHeight;
    int width;
    int fontHeight;
    int maxWidth;
    int i;
    int captured;
    int left;
    int top;

    font_SetFont(4);
    fontHeight = font_FontHeight();
    if (picture != 0)
        gr_BitMapSize(&size, picture);
    if (picture != 0)
        pictureHeight = size.height + 2;
    else
        pictureHeight = 0;
    height = fontHeight * count + pictureHeight + 8;
    maxWidth = 0x32;
    for (i = 0; i < count; ++i) {
        width = font_StringWidth(strings[i]);
        if (width > maxWidth)
            maxWidth = width;
    }
    width = maxWidth + 8;
    pictureBitmap = picture;
    pictureLineCount = count;
    pictureLines = strings;
    GetClientRect(rootWnd, &client);
    rect.left = (client.right - width) >> 1;
    rect.right = rect.left + width;
    rect.top = (client.bottom - height) >> 1;
    rect.bottom = rect.top + height;

    win_LockWin(0x1e00);
    win_Open(0x1e00, rect.left, rect.top, rect.right, rect.bottom);
    captured = MySetCapture(win_hwnd[6]);
    win_UnlockWin(0x1e00);
    win_GetObjRect(0x1e00, &rect);
    DialogWaitInit(0xf);
    win_MakeObjSelectable(0x1e01);
    win_FlushEvents();

    while (!DialogAbortOrCont()) {
        if (!win_GetEvent(&event))
            continue;
        if (event.object != 0x1e00)
            continue;
        event.object = 0;
        MessageBeep(0);
        if (!win_IsWinInFront(0x1e00)) {
            MSClipStart(win_hwnd[6]);
            win_DrawWindow(0x1e00);
            MSClipEnd();
            MySetCapture(win_hwnd[6]);
        }
        if (DialogAbortOrCont()) {
            DialogDone();
            break;
        }
    }
    DialogDone();
    if (captured && IsWindowVisible(captured))
        MySetCapture(captured);
    else
        MyReleaseCapture();
    win_Close(0x1e00);
    UpdateAllWindows();
    font_SetFont(0);
}






