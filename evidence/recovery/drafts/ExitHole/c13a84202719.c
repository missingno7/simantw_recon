extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern int far ListIndexA;
extern unsigned char near MapA[];
extern int far IsValidA(int x, int y);

int far ExitHole(int x, int y, int attribute, int mode, int stamina)
{
    register int direction;
    int displacement;
    int source;

    direction = 0;
    while (direction < 8) {
        if (IsValidA(x + (signed char)Dx8[direction],
                     y + (signed char)Dy8[direction]) == 1 &&
            MapA[(x + (signed char)Dx8[direction]) * 64 +
                 (y + (signed char)Dy8[direction])] < 0x50)
            break;
        ++direction;
    }
    if (direction == 8)
        return 0;

    Dx8[ListIndexA + 0x23a4] = (unsigned char)(x + (signed char)Dx8[direction]);
    Dx8[ListIndexA + 0x278e] = (unsigned char)(y + (signed char)Dy8[direction]);
    Dx8[ListIndexA + 0x2f62] = (unsigned char)attribute;
    Dx8[ListIndexA + 0x2b78] = (unsigned char)mode;
    if (mode == 6)
        Dx8[ListIndexA + 0x334c] = (unsigned char)stamina;
    else
        Dx8[ListIndexA + 0x334c] = 0;

    if (mode != 3 && mode != 7 &&
        (((attribute & 0x80) && x > 0x40) ||
         (!(attribute & 0x80) && x < 0x40)))
        Dx8[ListIndexA + 0x334c] = 0x78;

    if (ListIndexA >= 1000)
        return 0;
    ++ListIndexA;

    displacement = 0;
    source = 0;
    while (source < ListIndexA) {
        if (Dx8[source + 0x2f62] != 0) {
            if (displacement != 0) {
                Dx8[displacement + source + 0x2f62] = Dx8[source + 0x2f62];
                Dx8[displacement + source + 0x23a4] = Dx8[source + 0x23a4];
                Dx8[displacement + source + 0x278e] = Dx8[source + 0x278e];
                Dx8[displacement + source + 0x2b78] = Dx8[source + 0x2b78];
                Dx8[displacement + source + 0x334c] = Dx8[source + 0x334c];
            }
        } else {
            --displacement;
        }
        ++source;
    }
    ListIndexA += displacement;
    return 1;
}
