/*
 * Force the mode decision to share a local index value across list field
 * accesses; the scalar Dx8 declaration follows the admitted reader form.
 */
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define AlistL(i) AT((i) + 0x23a4)
#define AlistC(i) AT((i) + 0x278e)
#define AlistT(i) AT((i) + 0x2f62)
#define AlistM(i) AT((i) + 0x2b78)
#define AlistS(i) AT((i) + 0x334c)

extern unsigned char near MapA[];
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;

void far ForceModeA(int index, int mode, int value)
{
    int i = index;
    int cell;

    switch (mode) {
    case 1:
        AlistT(i) += 8;
        AlistM(i) = (unsigned char)value;
        AlistS(i) = 0;
        break;
    case 2:
    case 6:
        AlistM(i) = (unsigned char)value;
        AlistS(i) = 0;
        break;
    case 3:
    case 7:
        AlistT(i) -= 8;
        cell = AlistL(i) * 64 + AlistC(i) + 0x28e8;
        if (MapA[cell] < 0x48)
            MapA[cell] = 0x48;
        AlistM(i) = (unsigned char)value;
        AlistS(i) = 0;
        break;
    case 5:
    case 9:
        AlistT(i) -= 0x18;
        AlistM(i) = (unsigned char)value;
        AlistS(i) = 0;
        break;
    case 4:
    case 8:
    default:
        break;
    }

    if (value == 6 && MePlane == 1)
        AlistS(i) = (unsigned char)(((MeLocY & 0xfc) << 2) | (MeLocX >> 3));
}
