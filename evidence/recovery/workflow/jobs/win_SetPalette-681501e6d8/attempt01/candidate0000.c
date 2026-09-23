/* Hypothesis: load palette resource 15, leave its colors unchanged for indexed
   display, quantize RGB colors for the 8-bit display palette, then rebuild the
   GDI palette.  The resource stores a format byte followed by sixteen RGB
   triples. */
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far db_ReleaseObject(int object, int kind);
extern unsigned char near displayType;
extern unsigned char far Dx8[];
extern int near paletteH;
extern int far pascal DeleteObject(int handle);
extern void InitPalette(void);

int far win_SetPalette(int value)
{
    unsigned int handle;
    unsigned char far *colors;
    unsigned int i;

    handle = db_LoadObject(value, 15, 0);
    if (handle == 0)
        return 0;
    colors = (unsigned char far *)mem_Lock(handle);
    if (colors != 0 && colors[1] == 0) {
        if (displayType == 0) {
            for (i = 0; i < 16; ++i) {
                unsigned char r, g, b;
                r = colors[2 + i * 3];
                g = colors[3 + i * 3];
                b = colors[4 + i * 3];
                ((unsigned char near *)0)[0];
                Dx8[0x8c40 + i] = (unsigned char)(
                    (r & 0x20) | ((g & 0x10) >> 1) | ((b & 0x10) >> 2) |
                    ((r & 0x10) >> 1) | ((g & 0x20) >> 3) | ((b & 0x20) >> 4));
            }
        } else if (displayType == 8) {
            /* Match every resource color against the 15 system entries. */
            for (i = 0; i < 16; ++i) {
                unsigned int j, best;
                unsigned long bestDistance;
                unsigned char r, g, b;
                r = colors[2 + i * 3];
                g = colors[3 + i * 3];
                b = colors[4 + i * 3];
                best = 0;
                bestDistance = 0xffffffffUL;
                for (j = 0; j < 15; ++j) {
                    int dr, dg, db;
                    unsigned long distance;
                    dr = (int)Dx8[0x8c41] - (int)r;
                    dg = (int)Dx8[0x8c42] - (int)g;
                    db = (int)Dx8[0x8c40] - (int)b;
                    distance = (unsigned long)(dr * dr) +
                               (unsigned long)(dg * dg) +
                               (unsigned long)(db * db);
                    if (distance < bestDistance) {
                        bestDistance = distance;
                        best = j;
                    }
                }
                Dx8[0x8c00 + i] = (unsigned char)best;
            }
        }
    }
    if (paletteH) {
        DeleteObject(paletteH);
        paletteH = 0;
    }
    InitPalette();
    mem_Unlock(handle);
    db_ReleaseObject(value, 15);
    return 1;
}
