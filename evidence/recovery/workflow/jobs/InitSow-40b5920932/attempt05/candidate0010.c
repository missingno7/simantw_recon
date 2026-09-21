/*
 * InitSow: place the two sowbugs (slots 2 and 1) at random map cells.
 * Each gets a random column (0..127) and row (0..63) in the near 128x64
 * MapA terrain; only a cell whose terrain code is below 16 is used.  The
 * position and a random direction (0..7) are recorded in the far PACK
 * SowX/SowY/SowDir slots, the original cell code is saved in SowSave and
 * the cell is overwritten with the SowTab code for that direction.  Slot 0
 * is never initialised here.
 */
extern int far SRand1(int range);
extern unsigned char near MapA[];
extern struct { int v[3]; } far SowX, SowY, SowDir, SowSave;
extern struct { unsigned char v[8]; } far SowTab;
#define SOWX(i) SowX.v[i]
#define SOWY(i) SowY.v[i]
#define SOWDIR(i) SowDir.v[i]
#define SOWSAVE(i) SowSave.v[i]
#define SOWTAB(i) SowTab.v[i]

void far InitSow(void)
{
    unsigned i;
    int x;
    int y;
    int cell;
    unsigned char near *p;

    for (i = 2; i; i -= 1) {
        x = SRand1(128);
        y = SRand1(64);
        cell = (x << 6) + y;
        if (MapA[cell] < 16) {
            SOWX(i) = x;
            SOWY(i) = y;
            SOWDIR(i) = SRand1(8);
            SOWSAVE(i) = MapA[cell];
            MapA[cell] = SOWTAB(SOWDIR(i));
        }
    }
}
