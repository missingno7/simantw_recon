/*
 * DrawDog: position the cached dog animation object, as the admitted
 * DrawSimBird does for the bird.  Nothing is drawn while the yard is for
 * sale (near ForSaleState nonzero).  The dog position (near DogX/DogY) is
 * offset by frame-dependent signed bytes from private tables: twelve
 * walking frames (tables at DGROUP 0x1918 and 0x1924) or the running
 * frames indexed from 12 (tables at 0x18d8 and 0x18dc, four entries).  An
 * existing object (private cached handle at 0x188e, initialised -1) is
 * repositioned with hanim_SetObjectPos(right, bottom, 0x2134 + frame,
 * yardAnimHandle, object, -1); otherwise it is added with
 * hanim_AddAnimObject(yardAnimHandle, right, bottom, 0x2134 + frame, -1)
 * and the returned handle cached.
 */
extern int near DogX;
extern int near DogY;
extern int near DogFrame;
extern int near ForSaleState;
extern int near yardAnimHandle;
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);

static int near dogObject = -1;
static char near dogRunX[4] = { 3, 0, 1, 4 };
static char near dogRunY[4] = { 4, 3, 7, 2 };
static char near dogWalkX[12] = { 1, 0, 1, 2, 0, 1, 2, 2, 2, 1, 0, 1 };
static char near dogWalkY[12] = { 0, 1, 0, 1, 2, 1, 2, 0, 0, 1, 2, 1 };

void far DrawDog(void)
{
    int right;
    int bottom;
    int frame;

    right = DogX;
    bottom = DogY;
    if (ForSaleState == 0) {
        frame = DogFrame;
        if (frame < 12) {
            right += dogWalkX[frame];
            bottom += dogWalkY[frame];
        } else {
            right += dogRunX[frame - 12];
            bottom += dogRunY[frame - 12];
        }
        if (dogObject != -1) {
            hanim_SetObjectPos(right, bottom, frame + 0x2134,
                               yardAnimHandle, dogObject, -1);
        } else {
            dogObject = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                            frame + 0x2134, -1);
        }
    }
}
