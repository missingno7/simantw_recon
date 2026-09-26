/* Cat animation displacement windows share one 40-byte initialized table.
   The four source views overlap at byte offsets 0, 2, 6 and 10; the accesses
   use the absolute CatFrame index, which accounts for those base offsets. */
extern int near CatFrame;
extern int near CatX;
extern int near CatY;
extern int near yardAnimHandle;
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);

static int near catObject = -1;
static signed char near catFrameData[40] = {
     0,   1,   2,   1,   2,   0,   2,   0,   1,   1,
     3,   3, -10,  -9, -10, -10, -21, -19, -18,   0,
     0,   2,   4,   6,   8,  10,  12,  14,  16,  18,
     0, -16, -23, -24, -22, -18, -10, -10,  -4,  -2
};
#define catFirstX  (catFrameData)
#define catSecondX (catFrameData + 2)
#define catSecondY (catFrameData + 6)
#define catFirstY  (catFrameData + 10)

void far DrawSimCat(void)
{
    int right;
    int bottom;

    right = CatX;
    bottom = CatY;
    if (CatFrame >= 10) {
        if (CatFrame < 20) {
            right += catSecondX[CatFrame];
            bottom += catSecondY[CatFrame];
        } else {
            right += catFirstX[CatFrame];
            bottom += catFirstY[CatFrame];
        }
    }

    if (catObject != -1) {
        hanim_SetObjectPos(right, bottom, CatFrame + 0x514,
                           yardAnimHandle, catObject, -1);
    } else {
        catObject = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                        CatFrame + 0x514, -1);
    }
}
