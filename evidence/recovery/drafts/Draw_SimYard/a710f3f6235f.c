/*
 * Hypothesis: redraw the yard scene through the cached animation set.  The
 * named animal coordinates and frame globals are used directly; each cached
 * object is created on first sight and repositioned on later passes.
 */
extern int near BirdFrame;
extern int near BirdOn;
extern int near BirdX;
extern int near BirdY;
extern int near BoyFrame;
extern int near BoyHere;
extern int near CatFrame;
extern int near CatOn;
extern int near CatX;
extern int near CatY;
extern int near DogFrame;
extern int near DogX;
extern int near DogY;
extern int near ForSaleState;
extern int near RainOn;
extern int near yardAnimHandle;
extern int near win_hwnd[];
extern int near patchRgn2[];
extern long far editMessage;
extern long far mapMessage;
extern long far mapMessageRemoveTime;
extern int far hanim_MakeAnimSet(void);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern void far hanim_RemoveAnimObject(int animation, int object,
                                       char far *name);
extern void far hanim_RenderAnimSet(unsigned int setHandle, int window,
                                    int left, int top, int a, int b,
                                    int size, int mode);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far DrawSimKid(void);
extern void far DrawMower(void);
extern void far DrawSwarm(void);
extern void far DrawRain(void);
extern void far InvertPatch(int x, int y);
extern int far win_IsWinOpen(int window);
extern unsigned long far TickCount(void);
extern int far ConvColor(int color);
extern void far font_SetFont(int font);
extern void far win_FillObjRect(int object, int color);
extern void far win_PrintfAtObj(int object, long message);

struct YardPoint {
    int x;
    int y;
};
extern struct YardPoint far CurYardPnt;

static int near dogObject = -1;
static int near catObject = -1;
static int near birdObject = -1;

void far Draw_SimYard(int mode, int selector)
{
    int x;
    int y;
    int frame;

    MSClipStart(win_hwnd[25]);
    if (patchRgn2[9] != 0) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        patchRgn2[9] = 0;
    }
    MSClipEnd();

    if (yardAnimHandle == 0)
        yardAnimHandle = hanim_MakeAnimSet();

    if (DogFrame >= 0) {
        x = DogX;
        y = DogY;
        frame = DogFrame + 0x2134;
        if (dogObject == -1)
            dogObject = hanim_AddAnimObject(yardAnimHandle, x, y,
                                             frame, -1);
        else
            hanim_SetObjectPos(x, y, frame, yardAnimHandle,
                               dogObject, -1);
    } else if (dogObject != -1) {
        hanim_RemoveAnimObject(yardAnimHandle, dogObject, "dog");
        dogObject = -1;
    }

    if (CatOn != 0) {
        x = CatX;
        y = CatY;
        frame = CatFrame + 0x514;
        if (catObject == -1)
            catObject = hanim_AddAnimObject(yardAnimHandle, x, y,
                                             frame, -1);
        else
            hanim_SetObjectPos(x, y, frame, yardAnimHandle,
                               catObject, -1);
    } else if (catObject != -1) {
        hanim_RemoveAnimObject(yardAnimHandle, catObject, "cat");
        catObject = -1;
    }

    if (BirdOn != 0) {
        x = BirdX - 0xa;
        y = BirdY - 3;
        if (BirdFrame != 0) {
            ++x;
            y += 2;
        }
        frame = BirdFrame + 0x4e2;
        if (birdObject == -1)
            birdObject = hanim_AddAnimObject(yardAnimHandle, x, y,
                                              frame, -1);
        else
            hanim_SetObjectPos(x, y, frame, yardAnimHandle,
                               birdObject, -1);
    } else if (birdObject != -1) {
        hanim_RemoveAnimObject(yardAnimHandle, birdObject, "bird");
        birdObject = -1;
    }

    if (BoyHere != 0 && BoyFrame >= 0)
        DrawSimKid();
    if (ForSaleState != 0)
        DrawMower();
    if (RainOn != 0)
        DrawRain();
    if (mode >= 0)
        DrawSwarm();

    hanim_RenderAnimSet(yardAnimHandle, 0x1900, 0, 0, 0, 0,
                        0x200, selector);
    MSClipEnd();

    if (win_hwnd[35] != 0 && win_IsWinOpen(0x1900) != 0) {
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
}
