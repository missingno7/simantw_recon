/* Candidate translation unit antedit_A998_DrawDog_2: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DrawDog, _DrawSimBird */

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
extern int near BirdX;
extern int near BirdY;
extern int near BirdFrame;
static int near birdObject = -1;

void far DrawDog(void)
{
    int right;
    int bottom;

    right = DogX;
    bottom = DogY;
    if (ForSaleState == 0) {
        if (DogFrame < 12) {
            right += dogWalkX[DogFrame];
            bottom += dogWalkY[DogFrame];
        } else {
            right += dogRunX[DogFrame - 12];
            bottom += dogRunY[DogFrame - 12];
        }
        if (dogObject != -1) {
            hanim_SetObjectPos(right, bottom, DogFrame + 0x2134,
                               yardAnimHandle, dogObject, -1);
        } else {
            dogObject = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                            DogFrame + 0x2134, -1);
        }
    }
}

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

