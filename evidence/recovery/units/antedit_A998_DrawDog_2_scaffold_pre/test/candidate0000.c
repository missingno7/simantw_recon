/* Candidate translation unit antedit_A998_DrawDog_2_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DrawDog, _DrawForSale
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern int near DogX;
extern int near DogY;
extern int near DogFrame;
extern int near ForSaleState;
extern int near yardAnimHandle;
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);
/* SCAFFOLD, not recovered source: the 68 bytes of private data between _DrawForSale and _DrawDog (DGROUP 1894-18D8, unclaimed members), copied from the image so the claimed pieces keep their layout. */
static unsigned char pool_data_fill_1894[68] = {0xA9, 0x00, 0x43, 0x00, 0xC0, 0x00, 0x43, 0x00, 0xB9, 0x00, 0x4A, 0x00, 0xA2, 0x00, 0x4A, 0x00, 0xA9, 0x00, 0x43, 0x00, 0xC1, 0x00, 0x43, 0x00, 0xBA, 0x00, 0x4A, 0x00, 0xA2, 0x00, 0x4A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x25, 0x73, 0x00, 0x28, 0x25, 0x64, 0x29, 0x00, 0x0A, 0x00, 0x25, 0x2D, 0x64, 0x00, 0x25, 0x2D, 0x64, 0x00, 0x25, 0x64, 0x00, 0x25, 0x64, 0x00, 0x25, 0x64, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00};
/* SCAFFOLD, not recovered source: the 56 bytes of private data between _DrawDog and _DrawDog (DGROUP 18E0-1918, unclaimed members), copied from the image so the claimed pieces keep their layout. */
static unsigned char pool_data_fill_18E0[56] = {0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x04, 0x05, 0x04, 0x06, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x02, 0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x6B, 0x69, 0x64, 0x62, 0x61, 0x6C, 0x6C, 0x6F, 0x6F, 0x6E, 0x00, 0x00};
static int near dogObject = -1;
static char near dogRunX[4] = { 3, 0, 1, 4 };
static char near dogRunY[4] = { 4, 3, 7, 2 };
static char near dogWalkX[12] = { 1, 0, 1, 2, 0, 1, 2, 2, 2, 1, 0, 1 };
static char near dogWalkY[12] = { 0, 1, 0, 1, 2, 1, 2, 0, 0, 1, 2, 1 };
/* SCAFFOLD, not recovered source: the 2 bytes of private data between _DrawDog and _DrawForSale (DGROUP 1890-1892, unclaimed members), copied from the image so the claimed pieces keep their layout. */
static unsigned char pool_data_fill_1890[2] = {0xFF, 0xFF};
static int near forSaleObject = -1;


void DrawForSale(void);

#pragma alloc_text(RUN2_TEXT, DrawForSale)

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

void DrawForSale(void)
{
    if (forSaleObject != -1) {
        hanim_SetObjectPos(0xaa, 0xba, 0x4ec, yardAnimHandle,
                           forSaleObject, -1);
    } else {
        forSaleObject = hanim_AddAnimObject(yardAnimHandle, 0xaa, 0xba,
                                            0x4ec, -1);
    }
}

