/*
 * SetDevicePalette: load a device colour table through the GDI Escape
 * interface.  The driver is first asked (QUERYESCSUPPORT, 8) whether it
 * supports SETCOLORTABLE (4, held in a stack word); if not, 0 is
 * returned.  A null colour pointer resets the device table with an
 * empty SETCOLORTABLE.  Otherwise a 0x42-byte stack table (first index,
 * count, up to sixteen COLORREF entries built with the RGB packing from
 * the far 4-byte palette entries, whose segment is kept in DS for the
 * loop) is sent with SETCOLORTABLE.  The escape word doubles as the loop
 * counter.  1 is returned.
 */
struct PalEntry {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char flags;
};

#define P_ p
struct ColorTable {
    unsigned char first;
    unsigned char count;
    unsigned long colors[16];
};

#define RGB(r, g, b) ((unsigned char)(r) | ((unsigned long)(unsigned char)(b) << 16) | ((unsigned)(g) << 8))

extern int far pascal Escape(int dc, int escape, int count, char far *input, char far *output);

int far SetDevicePalette(int dc, int first, int count, struct PalEntry far *colors)
{
    int n;
    int ok;
    struct PalEntry far *p;
    struct ColorTable table;

    n = 4;
    ok = Escape(dc, 8, 2, (char far *)&n, (char far *)0);
    if (ok == 0)
        return ok;
    p = colors;
    if (p != (struct PalEntry far *)0) {
        table.first = first;
        table.count = count;
        for (n = 0; n < count; n++)
            table.colors[n] = RGB(P_[n].red, P_[n].green, P_[n].blue);
        Escape(dc, 4, 0x42, (char far *)&table, (char far *)0);
    } else {
        Escape(dc, 4, 0, (char far *)0, (char far *)0);
    }
    return 1;
}
