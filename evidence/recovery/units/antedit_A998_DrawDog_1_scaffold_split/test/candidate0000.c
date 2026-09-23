/* Candidate translation unit antedit_A998_DrawDog_1_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DrawDog
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern int near DogX;
extern int near DogY;
extern int near DogFrame;
extern int near ForSaleState;
extern int near yardAnimHandle;
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);
/* SCAFFOLD, not recovered source: static data of unclaimed members between _DrawDog and _DrawDog (DGROUP 1890-18D8), copied from the image so the claimed pieces keep their layout. */
static unsigned char pool_data_fill_1890[72] = {0xFF, 0xFF, 0xFF, 0xFF, 0xA9, 0x00, 0x43, 0x00, 0xC0, 0x00, 0x43, 0x00, 0xB9, 0x00, 0x4A, 0x00, 0xA2, 0x00, 0x4A, 0x00, 0xA9, 0x00, 0x43, 0x00, 0xC1, 0x00, 0x43, 0x00, 0xBA, 0x00, 0x4A, 0x00, 0xA2, 0x00, 0x4A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x25, 0x73, 0x00, 0x28, 0x25, 0x64, 0x29, 0x00, 0x0A, 0x00, 0x25, 0x2D, 0x64, 0x00, 0x25, 0x2D, 0x64, 0x00, 0x25, 0x64, 0x00, 0x25, 0x64, 0x00, 0x25, 0x64, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00};
/* SCAFFOLD, not recovered source: static data of unclaimed members between _DrawDog and _DrawDog (DGROUP 18E0-1918), copied from the image so the claimed pieces keep their layout. */
static unsigned char pool_data_fill_18E0[56] = {0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x04, 0x05, 0x04, 0x06, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x02, 0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x6B, 0x69, 0x64, 0x62, 0x61, 0x6C, 0x6C, 0x6F, 0x6F, 0x6E, 0x00, 0x00};
static int near dogObject = -1;
static char near dogRunX[4] = { 3, 0, 1, 4 };
static char near dogRunY[4] = { 4, 3, 7, 2 };
static char near dogWalkX[12] = { 1, 0, 1, 2, 0, 1, 2, 2, 2, 1, 0, 1 };
static char near dogWalkY[12] = { 0, 1, 0, 1, 2, 1, 2, 0, 0, 1, 2, 1 };




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

