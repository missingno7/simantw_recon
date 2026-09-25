/*
 * Hypothesis: position the cached bird animation object from the current
 * bird coordinates and frame.  A missing object is added once and its
 * returned handle is retained in the private near slot.
 */
extern int near BirdX;
extern int near BirdY;
extern int near BirdFrame;
extern int near yardAnimHandle;
static int near birdObject = -1;

extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);

void far DrawSimBird(void)
{
    int right;
    int bottom;

    right = BirdX - 0xa;
    bottom = BirdY - 3;
    if (BirdFrame != 0) {
        ++right;
        bottom += 2;
    }
    if (birdObject != -1) {
        hanim_SetObjectPos(right, bottom, BirdFrame + 0x4e2,
                           yardAnimHandle, birdObject, -1);
    } else {
        birdObject = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                         BirdFrame + 0x4e2, -1);
    }
}
