struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
/* Complete control-flow reconstruction of the yard animation and map draw. */
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
extern unsigned int near mapBuf;

extern int far yardBalloonHandle;
extern int far yardBalloon;
extern long far mapMessage;

extern long far editMessage;

extern long far mapMessageRemoveTime;

struct YardPoint { int x; int y; };
extern struct YardPoint far CurYardPnt;
struct YardRect { int left; int top; int right; int bottom; };
extern struct Rect far mapTileRect;


extern unsigned int far hanim_MakeAnimSet(void);

extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern void far hanim_RemoveAnimObject(int animation, int object,
                                       char far *name);
extern void far hanim_RenderAnimSet(int setHandle, int window,
                                    int left, int top, unsigned long buffer,
                                    int mode, int size);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far DrawSimKid(void);
extern void far DrawMower(void);
extern void far DrawSwarm(void);
extern void far mem_Free(int handle);
extern void far InvertPatch(int x, int y);
extern int far win_IsWinOpen(int window);
extern unsigned long far TickCount(void);
extern int far ConvColor(int color);
extern void far font_SetFont(int font);
extern void far win_FillObjRect(int object, int color);
extern void far win_PrintfAtObj(int object, long message);
extern void far win_GetObjRect(int object, struct WinRect far *rect);

extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);

extern void AllocateMapBuffer(void);

extern void far *mem_Lock(unsigned int handle);

extern int far mem_Unlock(unsigned int handle);

extern void myServiceSong(void);

extern int far SRand1(int limit);

struct YardWalkCatView {
    signed char walkY[8];
    signed char catFrameOffsets[40];
};
static struct YardWalkCatView near dogWalkCatData = {
    {0, 1, 0, 1, 2, 1, 2, 0},
    {0, 1, 2, 1, 2, 0, 2, 0, 1, 1, 3, 3, -10, -9, -10, -10,
     -21, -19, -18, 0, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18,
     0, -16, -23, -24, -22, -18, -10, -10, -4, -2}
};
struct YardPrivateData {
    int drawFlag;
    unsigned char formatRegion[34];
    signed char dogRunX[4];
    signed char dogRunY[4];
    unsigned char kidAnimationData[56];
    signed char dogWalkX[12];
};
static struct YardPrivateData near yardPrivateData = {
    1,
    {0x00,0x00,0x25,0x73,0x00,0x28,0x25,0x64,0x29,0x00,0x0a,0x00,
     0x25,0x2d,0x64,0x00,0x25,0x2d,0x64,0x00,0x25,0x64,0x00,0x25,
     0x64,0x00,0x25,0x64,0x00,0x00,0x03,0x03,0x01,0x00},
    {3, 0, 1, 4},
    {4, 3, 7, 2},
    {2,0,2,3,2,3,2,0,2,3,2,3,4,5,4,6,0,2,0,2,0,3,2,1,5,0,0,0,
     0,0,0,0,1,0,1,1,0,1,1,0,1,1,0,1,0x6b,0x69,0x64,0x62,0x61,
     0x6c,0x6c,0x6f,0x6f,0x6e,0,0},
    {1,0,1,2,0,1,2,2,2,1,0,1}
};
#define dogWalkYAndCatOffsets (dogWalkCatData.walkY)
#define catFrameOffsets (dogWalkCatData.catFrameOffsets)
#define catFirstX (catFrameOffsets)
#define catSecondX (catFrameOffsets + 2)
#define catSecondY (catFrameOffsets + 6)
#define catFirstY (catFrameOffsets + 10)
#define dogWalkX (yardPrivateData.dogWalkX)
#define dogRunX (yardPrivateData.dogRunX)
#define dogRunY (yardPrivateData.dogRunY)

static int near kidObject = -1;
static int near catObject = -1;
static int near birdObject = -1;
static int near dogObject = -1;
static int near unusedObject = -1;
static int near forSaleObject = -1;
union RainHandles15 {
    int handle[15];
    unsigned char bytes[30];
};
union RainHandles17 {
    int handle[17];
    unsigned char bytes[34];
};
static union RainHandles15 near rainObjects;
static union RainHandles17 near rainObjectTableA;
static union RainHandles17 near rainObjectTableB;

void far Draw_SimYard(int mode, int selector)
{
    int i;
    int x;
    int y;
    int frame;
    int far *balloonHandle;
    long now;
    unsigned long lockedBuffer;

    MSClipStart(win_hwnd[25]);
    if (patchRgn2[9] != 0) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        patchRgn2[9] = 0;
    }
    MSClipEnd();

    if (mode <= 1)
        goto normal_yard;
    goto invalidate_yard;

normal_yard:
    if (yardAnimHandle == 0) {
        yardAnimHandle = hanim_MakeAnimSet();
        kidObject = -1;
        catObject = -1;
        birdObject = -1;
        dogObject = -1;
        unusedObject = -1;
        forSaleObject = -1;
        yardBalloonHandle = -1;
        for (i = 0; i < 30; ++i)
            rainObjects.bytes[i] = 0xff;
        for (i = 0; i < 34; ++i) {
            rainObjectTableA.bytes[i] = 0xff;
            rainObjectTableB.bytes[i] = 0xff;
        }
    }

    if (CatOn != 0) {
        x = CatX;
        y = CatY;
        frame = CatFrame;
        if (frame >= 10) {
            if (frame < 20) {
                x += catSecondX[frame];
                y += catSecondY[frame];
            } else {
                x += catFirstX[frame];
                y += catFirstY[frame];
            }
        }
        if (catObject != -1)
            hanim_SetObjectPos(x, y, frame + 0x514,
                               yardAnimHandle, catObject, -1);
        else
            catObject = hanim_AddAnimObject(yardAnimHandle, x, y,
                                            frame + 0x514, -1);
    } else if (catObject != -1) {
        hanim_RemoveAnimObject(yardAnimHandle, catObject, "cat");
        catObject = -1;
    }
    myServiceSong();

    if (ForSaleState == 0) {
        x = DogX;
        y = DogY;
        frame = DogFrame;
        if (frame < 12) {
            x += dogWalkX[frame];
            y += dogWalkYAndCatOffsets[frame];
        } else {
            x += dogRunX[frame - 12];
            y += dogRunY[frame - 12];
        }
        if (dogObject != -1)
            hanim_SetObjectPos(x, y, frame + 0x2134,
                               yardAnimHandle, dogObject, -1);
        else
            dogObject = hanim_AddAnimObject(yardAnimHandle, x, y,
                                            frame + 0x2134, -1);
    }
    myServiceSong();

    if (selector == 0) {
        if (BoyHere != 0 && BoyFrame >= 0) {
            DrawSimKid();
        } else {
            if (kidObject != -1) {
                hanim_RemoveAnimObject(yardAnimHandle, kidObject, "boy");
                kidObject = -1;
            }

            balloonHandle = &yardBalloonHandle;
            if (*balloonHandle != -1) {
                    hanim_RemoveAnimObject(yardAnimHandle,
                                           *balloonHandle, "balloon");
                    *balloonHandle = -1;
            }
            if (yardBalloon != 0) {
                mem_Free(yardBalloon);
                yardBalloon = 0;
            }
            myServiceSong();
        }
    }

    DrawMower();

    if (BirdOn != 0) {
        x = BirdX - 10;
        y = BirdY - 3;
        if (BirdFrame != 0) {
            ++x;
            y += 2;
        }
        if (birdObject != -1)
            hanim_SetObjectPos(x, y, BirdFrame + 0x4e2,
                               yardAnimHandle, birdObject, -1);
        else
            birdObject = hanim_AddAnimObject(yardAnimHandle, x, y,
                                             BirdFrame + 0x4e2, -1);
    } else if (birdObject != -1) {
        hanim_RemoveAnimObject(yardAnimHandle, birdObject, "bird");
        birdObject = -1;
    }

    if (ForSaleState != 0) {
        if (forSaleObject != -1)
            hanim_SetObjectPos(0xaa, 0xba, 0x4ec, yardAnimHandle,
                               forSaleObject, -1);
        else
            forSaleObject = hanim_AddAnimObject(yardAnimHandle, 0xaa, 0xba,
                                                0x4ec, -1);
    }
    myServiceSong();

    if (RainOn != 0) {
        for (i = 14; i > 0; --i) {
            x = SRand1(0x190) + 0x32;
            y = SRand1(0x96);
            if (rainObjects.handle[i] != -1)
                hanim_SetObjectPos(x, y, 0x1b5d, yardAnimHandle,
                                   rainObjects.handle[i], 0x8000);
            else
                rainObjects.handle[i] = hanim_AddAnimObject(yardAnimHandle,
                                                           x, y, 0x1b5d,
                                                           0x3e8);
        }
    } else {
        for (i = 0; i < 15; ++i) {
            if (rainObjects.handle[i] != -1) {
                hanim_RemoveAnimObject(yardAnimHandle,
                                       rainObjects.handle[i], "rain");
                rainObjects.handle[i] = -1;
            }
        }
    }
    myServiceSong();
    DrawSwarm();

    MSClipStart(win_hwnd[25]);
    if (patchRgn2[9] == 0) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        patchRgn2[9] = 1;
    }
    MSClipEnd();

    if (win_hwnd[35] != 0 && win_IsWinOpen(0x1900) != 0) {
        MSClipStart(win_hwnd[25]);
        now = TickCount();
        if (now > mapMessageRemoveTime) {
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

    AllocateMapBuffer();
    lockedBuffer = mem_Lock(mapBuf);
    hanim_RenderAnimSet(yardAnimHandle, 0x1900,
                       mapTileRect.left, mapTileRect.top,
                       lockedBuffer, 0x200, 0xe2);
    mem_Unlock(mapBuf);
    myServiceSong();
    return;

invalidate_yard:
    {
        struct YardRect rect;

        MSClipStart(win_hwnd[25]);
        if (patchRgn2[9] == 0) {
            InvertPatch(CurYardPnt.x, CurYardPnt.y);
            patchRgn2[9] = 1;
        }
        MSClipEnd();

        win_GetObjRect(0x1902, &rect);
        InvalidateRect(win_hwnd[25], &rect, 0);
        if (win_hwnd[35] != 0 && win_IsWinOpen(0x1900) != 0) {
            MSClipStart(win_hwnd[25]);
            now = TickCount();
            if (now > mapMessageRemoveTime) {
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
}
