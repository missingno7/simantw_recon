/*
 * Force the mode decision to share a local index value across list field
 * accesses; the scalar Dx8 declaration follows the admitted reader form.
 */
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define AlistL(index) AT((index) + 0x23a4)
#define AlistC(index) AT((index) + 0x278e)
#define AlistT(index) AT((index) + 0x2f62)
#define AlistM(index) AT((index) + 0x2b78)
#define AlistS(index) AT((index) + 0x334c)

extern unsigned char near MapA[];
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;

void far ForceModeA(int index, int mode, int value)
{
    int i = index;
    volatile int cell;

    switch (mode) {
    case 1:
        AlistT(index) += 8;
        AlistM(index) = (unsigned char)value;
        AlistS(index) = 0;
        break;
    case 2:
    case 6:
        AlistM(index) = (unsigned char)value;
        AlistS(index) = 0;
        break;
    case 3:
    case 7:
        AlistT(index) -= 8;
        cell = AlistL(index) * 64 + AlistC(index) + 0x28e8;
        if (MapA[cell] < 0x48)
            MapA[cell] = 0x48;
        AlistM(index) = (unsigned char)value;
        AlistS(index) = 0;
        break;
    case 5:
    case 9:
        AlistT(index) -= 0x18;
        AlistM(index) = (unsigned char)value;
        AlistS(index) = 0;
        break;
    case 4:
    case 8:
    default:
        break;
    }

    if (value == 6 && MePlane == 1)
        AlistS(index) = (unsigned char)(((MeLocY & 0xfc) << 2) | (MeLocX >> 3));
}
