/* Hypothesis: resource 15 is a 16-color RGB palette.  Zero format uses the
   indexed-display bit packing; 8-bit display remaps against the system table
   in Dx8 before refreshing the GDI palette. */
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
    signed char format;
    int i;

    handle = db_LoadObject(value, 15, 0);
    if (handle == 0)
        return 0;
    colors = (unsigned char far *)mem_Lock(handle);
    format = colors[1];
    if (format == 0) {
        if (displayType == 0) {
            unsigned char converted[16];
            unsigned char far *p;
            p = colors + 2;
            for (i = 0; i < 16; ++i) {
                unsigned char c, d, e;
                c = p[0];
                d = p[1];
                e = p[2];
                converted[i] = (unsigned char)((c & 0x20) |
                    (((((e & 0x10) >> 1 | (d & 0x10)) >> 1 |
                       (e & 0x20) | (c & 0x10)) >> 1 |
                      (d & 0x20)) >> 1));
                p += 3;
            }
        } else if (displayType == 8) {
            /* Choose the closest of the fifteen system colors per entry. */
            unsigned char far *table;
            table = Dx8;
            for (i = 0; i < 16; ++i) {
                int j;
                unsigned long best;
                unsigned char far *q;
                q = colors + 2 + i * 3;
                best = 0xffffffffUL;
                for (j = 0; j < 15; ++j) {
                    int dr, dg, db;
                    unsigned long distance;
                    dr = (int)table[0x8c44 + j * 4] - (int)q[0];
                    dg = (int)table[0x8c45 + j * 4] - (int)q[1];
                    db = (int)table[0x8c46 + j * 4] - (int)q[2];
                    distance = (unsigned long)(dr * dr) +
                               (unsigned long)(dg * dg) +
                               (unsigned long)(db * db);
                    if (distance < best)
                        best = distance;
                }
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




