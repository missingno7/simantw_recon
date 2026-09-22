/* Supervisor hypothesis: Private initialized cached animation handle, with -1 as the missing-object sentinel; full DATA bytes must independently match. */
/*
 * Keep the single for-sale animation object positioned at the fixed yard
 * rectangle.  A missing cached object is created with the same geometry and
 * its returned handle is retained for subsequent redraws.
 */
static int near forSaleObject = -1;
extern int near yardAnimHandle;
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);

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
