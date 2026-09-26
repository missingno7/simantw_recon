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

static int near dogObject = -1;
static int near catObject = -1;
static int near birdObject = -1;

void far Draw_SimYard(int mode, int selector)
{
    int x;
    int y;
    int frame;

    if (yardAnimHandle == 0)
        yardAnimHandle = hanim_MakeAnimSet();

    MSClipStart(win_hwnd[25]);

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
}
