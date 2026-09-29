/* Hypothesis: resource 15 is a 16-color RGB palette.  Zero format uses the
   indexed-display bit packing; 8-bit display remaps against the system table
   in Dx8 before refreshing the GDI palette. */
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void db_ReleaseObject(unsigned int object, int type);

extern unsigned char near displayType;
extern unsigned char far Dx8[];
extern int near paletteH;
extern int far pascal DeleteObject(int handle);
extern void InitPalette(void);

int far win_SetPalette(int value)
{
    unsigned int handle;
    unsigned char far *colors;
    int format;
    int i;
    unsigned char converted[16];
    unsigned char far *p;
    unsigned char far *table;
    unsigned char far *systemColors;
    unsigned char far *q;
    int j; unsigned int dr, dg, db;
    int baseR, baseG, baseB;
    unsigned char far *systemEnd;
    unsigned long best, distance;

    handle = db_LoadObject(value, 15, 0);
    if (handle == 0)
        return 0;
    colors = (unsigned char far *)mem_Lock(handle);
    format = (signed char)colors[1];
    if (format == 0) {
        if (displayType == 0) {
            p = colors + 2;
            i = format;
            do {
                unsigned char c, d, e;
                c = p[0];
                d = p[1];
                e = p[2];
                converted[i] = (unsigned char)((c & 0x20) |
                    (((((e & 0x10) >> 1 | (d & 0x10)) >> 1 |
                       (e & 0x20) | (c & 0x10)) >> 1 |
                      (d & 0x20)) >> 1));
                p += 3;
            } while (++i < 16);
        } else if (displayType == 8) {
            /* Choose the closest of the fifteen system colors per entry. */
            baseG = Dx8[0x8c41];
            baseB = Dx8[0x8c42];
            baseR = Dx8[0x8c40];
            p = colors + 2;
            i = 16;
            do {
                dr = (int)Dx8[0x8c40] - (int)p[0];
                dg = (int)Dx8[0x8c41] - (int)p[1];
                db = (int)Dx8[0x8c42] - (int)p[2];
                best = (unsigned long)(dr * dr) +
                       (unsigned long)(dg * dg) +
                       (unsigned long)(db * db);
                systemColors = Dx8 + 0x8c45;
                systemEnd = Dx8 + 0x8c81;
                for (; systemColors < systemEnd; systemColors += 4) {
                    dr = (int)systemColors[-1] - (int)p[0];
                    dg = (int)systemColors[0] - (int)p[1];
                    db = (int)systemColors[1] - (int)p[2];
                    distance = (unsigned long)(dr * dr) +
                               (unsigned long)(dg * dg) +
                               (unsigned long)(db * db);
                    if (distance < best)
                        best = distance;
                }
                p += 3;
            } while (--i);
            q = colors + 2;
            for (i = 0; i < 16; ++i) {
                Dx8[0x8c40 + i * 4] = q[0];
                Dx8[0x8c00 + i * 4] = q[0];
                Dx8[0x8c41 + i * 4] = q[1];
                Dx8[0x8c01 + i * 4] = q[1];
                Dx8[0x8c42 + i * 4] = q[2];
                Dx8[0x8c02 + i * 4] = q[2];
                q += 3;
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





