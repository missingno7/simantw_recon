/*
 * DrawSimKid: position/animate the yard boy character and his speech
 * balloon.  right/bottom start at BoyX/BoyY and get a per-frame delta from
 * one of three private byte-delta tables (walk: frame<12, run: frame<24
 * indexed frame-12, stand: frame<200 indexed by frame directly, matching
 * the observed [bx+disp] addressing with no subtraction); frame>=200 skips
 * the delta entirely.  The cached kid animation object (near word,
 * sentinel -1) is created/repositioned with hanim_*AnimObject exactly like
 * the admitted DrawSimBird/DrawDog.  Once GamePaused is false and
 * MacTickCount() has passed BoyMsgCnt, BoyMessOn is cleared.  The cached
 * far balloon object/window handles (yardBalloonHandle, yardBalloon; PACK
 * segment, same as mapTileRect/BlkWarnHealth) are torn down whenever
 * present; while BoyMessOn is set, a new balloon is built from
 * BoyMsgs[BoyMsgOffset] (a far pointer table) and locked to read its
 * height field (+0xa), which offsets the balloon's Y position above the
 * mapTileRect top edge.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

struct BalloonInfo {
    unsigned char pad[0xa];
    int height;
};

static signed char near boyWalkDX[12] = { 1, 0, 1, 2, 0, 1, 2, 2, 2, 1, 0, 1 };
static signed char near boyWalkDY[12] = { 0, 1, 0, 1, 2, 1, 2, 0, 0, 1, 2, 1 };
static signed char near boyRunDX[12] = { 3, 0, 1, 4, 2, 1, 3, 0, 1, 4, 2, 1 };
static signed char near boyRunDY[12] = { 4, 3, 7, 2, 4, 3, 7, 2, 4, 3, 7, 2 };
static signed char near boyStandDX[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static signed char near boyStandDY[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int near boyObject = -1;

extern int near BoyFrame;
extern int near BoyX;
extern int near BoyY;
extern int near yardAnimHandle;
extern int far GamePaused;
extern long far BoyMsgCnt;
extern int far BoyMessOn;
extern int far BoyMsgOffset;
extern char far * far *BoyMsgs;
extern int far yardBalloonHandle;
extern int far yardBalloon;
extern struct Rect far mapTileRect;
extern struct BalloonInfo far *yardBalloonPtr;

extern long far MacTickCount(void);
extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);
extern void far hanim_RemoveAnimObject(int animation, int object, char far *name);
extern void far mem_Free(int handle);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far font_SetFont(int font);
extern int far MakeBalloon(char far *text, int flag);

void far DrawSimKid(void)
{
    int right;
    int bottom;
    signed char dy;

    right = BoyX;
    bottom = BoyY;

    if (BoyFrame < 12) {
        right += boyWalkDX[BoyFrame];
        dy = boyWalkDY[BoyFrame];
        goto addY;
    }
    if (BoyFrame < 24) {
        right += boyRunDX[BoyFrame - 12];
        dy = boyRunDY[BoyFrame - 12];
        goto addY;
    }
    if (BoyFrame < 200) {
        right += boyStandDX[BoyFrame];
        dy = boyStandDY[BoyFrame];
    } else {
        goto skipY;
    }
addY:
    bottom += dy;
skipY:

    if (boyObject != -1) {
        hanim_SetObjectPos(right, bottom, BoyFrame + 0x1f40, yardAnimHandle, boyObject, -1);
    } else {
        boyObject = hanim_AddAnimObject(yardAnimHandle, right, bottom, BoyFrame + 0x1f40, -1);
    }

    if (!GamePaused) {
        if (MacTickCount() > BoyMsgCnt) {
            BoyMessOn = 0;
        }
    }

    if (yardBalloonHandle != -1) {
        hanim_RemoveAnimObject(yardAnimHandle, yardBalloonHandle, "boy");
        yardBalloonHandle = -1;
    }

    if (yardBalloon != 0) {
        mem_Unlock(yardBalloon);
        mem_Free(yardBalloon);
        yardBalloon = 0;
    }

    if (BoyMessOn != 0) {
        font_SetFont(2);
        yardBalloon = MakeBalloon(BoyMsgs[BoyMsgOffset], 0);
        font_SetFont(0);

        yardBalloonPtr = (struct BalloonInfo far *)mem_Lock(yardBalloon);
        right += 4;
        bottom = mapTileRect.top - yardBalloonPtr->height + BoyY;

        if (yardBalloonHandle != -1) {
            hanim_SetObjectPos(right, bottom, 0x7530, yardAnimHandle, yardBalloonHandle, 0x3e7);
        } else {
            yardBalloonHandle = hanim_AddAnimObject(yardAnimHandle, right, bottom, 0x7530, 0x3e7);
        }
    }
}
