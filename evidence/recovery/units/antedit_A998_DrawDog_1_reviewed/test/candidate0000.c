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
 * and the returned handle cached.  DogFrame is used directly and the
 * compiler keeps it in DX as a common subexpression.
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

/* The two pool_data_fill arrays contain exact initialized bytes at the
 * measured gaps 1890-18D8 and 18E0-1918. They stand in for unclaimed
 * neighbouring objects; their identities and source declarations remain
 * unrecovered. DrawDog's five named statics retain their own target bytes. */
static int near dogObject = -1;
static unsigned char pool_data_fill_1890[72] = {0xFF, 0xFF, 0xFF, 0xFF, 0xA9, 0x00, 0x43, 0x00, 0xC0, 0x00, 0x43, 0x00, 0xB9, 0x00, 0x4A, 0x00, 0xA2, 0x00, 0x4A, 0x00, 0xA9, 0x00, 0x43, 0x00, 0xC1, 0x00, 0x43, 0x00, 0xBA, 0x00, 0x4A, 0x00, 0xA2, 0x00, 0x4A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x25, 0x73, 0x00, 0x28, 0x25, 0x64, 0x29, 0x00, 0x0A, 0x00, 0x25, 0x2D, 0x64, 0x00, 0x25, 0x2D, 0x64, 0x00, 0x25, 0x64, 0x00, 0x25, 0x64, 0x00, 0x25, 0x64, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00};
static char near dogRunX[4] = { 3, 0, 1, 4 };
static char near dogRunY[4] = { 4, 3, 7, 2 };
static unsigned char pool_data_fill_18E0[56] = {0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x04, 0x05, 0x04, 0x06, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x02, 0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x6B, 0x69, 0x64, 0x62, 0x61, 0x6C, 0x6C, 0x6F, 0x6F, 0x6E, 0x00, 0x00};
static char near dogWalkX[12] = { 1, 0, 1, 2, 0, 1, 2, 2, 2, 1, 0, 1 };
static char near dogWalkY[12] = { 0, 1, 0, 1, 2, 1, 2, 0, 0, 1, 2, 1 };

void far pool_stub_data_context(void);
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_data_context)
void far pool_stub_data_context(void) { }

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
