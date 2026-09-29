/*
 * Force the mode decision to share a local index value across list field
 * accesses; the scalar Dx8 declaration follows the admitted reader form.
 */
extern unsigned char far Dx8[];

extern unsigned char near MapA[];
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;

void far ForceModeA(int index, int mode, int value)
{
    volatile int cell;
    volatile unsigned char far *entry;

    switch (mode) {
    case 1:
        entry = Dx8;
        entry[index + 0x2f62] += 8;
        entry[index + 0x2b78] = (unsigned char)value;
        entry[index + 0x334c] = 0;
        break;
    case 2:
    case 6:
        entry = Dx8;
        entry[index + 0x2b78] = (unsigned char)value;
        entry[index + 0x334c] = 0;
        break;
    case 3:
    case 7:
        entry = Dx8;
        entry[index + 0x2f62] -= 8;
        cell = entry[index + 0x23a4] * 64 + entry[index + 0x278e] + 0x28e8;
        if (MapA[cell] < 0x48)
            MapA[cell] = 0x48;
        entry[index + 0x2b78] = (unsigned char)value;
        entry[index + 0x334c] = 0;
        break;
    case 5:
    case 9:
        entry = Dx8;
        entry[index + 0x2f62] -= 0x18;
        entry[index + 0x2b78] = (unsigned char)value;
        entry[index + 0x334c] = 0;
        break;
    case 4:
    case 8:
    default:
        break;
    }

    if (value == 6 && MePlane == 1) {
        entry = Dx8;
        entry[index + 0x334c] = (unsigned char)(((MeLocY & 0xfc) << 2) | (MeLocX >> 3));
    }
}
