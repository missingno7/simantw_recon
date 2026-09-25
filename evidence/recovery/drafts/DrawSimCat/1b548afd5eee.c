/* Draw the cat's current animation frame. The short initial frame range and
 * the following range use separate signed displacement tables; positions
 * are then passed to the animation manager, creating the cached object once. */
extern int near CatFrame;
extern int near CatX;
extern int near CatY;
extern int near yardAnimHandle;
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);

static int near catObject = -1;
static char near catFirstX[10] = {0};
static char near catFirstY[10] = {0};
static char near catSecondX[20] = {0};
static char near catSecondY[20] = {0};

void far DrawSimCat(void)
{
    int right;
    int bottom;

    right = CatX;
    bottom = CatY;
    if (CatFrame < 10) {
        right += catFirstX[CatFrame];
        bottom += catFirstY[CatFrame];
    } else if (CatFrame < 20) {
        right += catSecondX[CatFrame];
        bottom += catSecondY[CatFrame];
    }

    if (catObject != -1) {
        hanim_SetObjectPos(right, bottom, CatFrame + 0x514,
                           yardAnimHandle, catObject, -1);
    } else {
        catObject = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                        CatFrame + 0x514, -1);
    }
}
