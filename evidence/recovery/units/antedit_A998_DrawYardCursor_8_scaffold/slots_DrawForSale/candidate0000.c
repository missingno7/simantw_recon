/* Supervisor hypothesis: Private initialized cached animation handle, with -1 as the missing-object sentinel; full DATA bytes must independently match. */
/*
 * Keep the single for-sale animation object positioned at the fixed yard
 * rectangle.  A missing cached object is created with the same geometry and
 * its returned handle is retained for subsequent redraws.
 */

extern int near yardAnimHandle;
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);

static int near dogObject = -1;
static unsigned char pool_data_fill_1890_prefix[2] = {0xFF, 0xFF};
static int near forSaleObject = -1;
static unsigned char pool_data_fill_1894[32] = {
    0xA9,0x00,0x43,0x00,0xC0,0x00,0x43,0x00,0xB9,0x00,0x4A,0x00,0xA2,0x00,0x4A,0x00,
    0xA9,0x00,0x43,0x00,0xC1,0x00,0x43,0x00,0xBA,0x00,0x4A,0x00,0xA2,0x00,0x4A,0x00
};
static int near yardDrawFlag = 1;
static unsigned char pool_data_fill_18B6[12] = {
    0x00,0x00,0x25,0x73,0x00,0x28,0x25,0x64,0x29,0x00,0x0A,0x00
};
static char near yardFormatBlackPopulation[4] = "%-d";
static char near yardFormatRedPopulation[4] = "%-d";
static char near yardFormatQueenStorage[3] = "%d";
static char near yardFormatBlackTotal[3] = "%d";
static char near yardFormatRedTotal[3] = "%d";
static unsigned char pool_data_fill_18D3[5] = {0x00,0x03,0x03,0x01,0x00};
static char near dogRunX[4] = {3,0,1,4};
static char near dogRunY[4] = {4,3,7,2};
static unsigned char pool_data_fill_18E0[56] = {
    0x02,0x00,0x02,0x03,0x02,0x03,0x02,0x00,0x02,0x03,0x02,0x03,0x04,0x05,0x04,0x06,
    0x00,0x02,0x00,0x02,0x00,0x03,0x02,0x01,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x01,0x00,0x01,0x01,0x00,0x01,0x01,0x00,0x01,0x01,0x00,0x01,0x6B,0x69,0x64,0x62,
    0x61,0x6C,0x6C,0x6F,0x6F,0x6E,0x00,0x00
};
static char near dogWalkX[12] = {1,0,1,2,0,1,2,2,2,1,0,1};
static char near dogWalkY[12] = {0,1,0,1,2,1,2,0,0,1,2,1};

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
