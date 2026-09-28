/* One-arm index temporary tests the MSC7-X2 source-order allocation rule. */
extern unsigned char far Dx8[];
#define AT(off) (Dx8[off])
#define BlistT(i) AT((i) + 0x3d18)
#define BlistM(i) AT((i) + 0x3b22)
#define BlistS(i) AT((i) + 0x3f0e)
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
void far ForceModeB(int index, int mode, int value)
{
    switch (mode) {
    case 1: {
        int updateIndex = index;
        BlistT(updateIndex) += 8;
        BlistM(updateIndex) = (unsigned char)value;
        BlistS(updateIndex) = 0;
        break;
    }
    case 2:
    case 6:
        BlistM(index) = (unsigned char)value;
        BlistS(index) = 0;
        break;
    case 3:
    case 7:
        BlistT(index) -= 8;
        BlistM(index) = (unsigned char)value;
        BlistS(index) = 0;
        break;
    case 5:
    case 9:
        BlistT(index) -= 0x18;
        BlistM(index) = (unsigned char)value;
        BlistS(index) = 0;
        break;
    case 4:
    case 8:
    default:
        break;
    }
    if (value == 6 && MePlane == 1)
        BlistS(index) = (unsigned char)(((MeLocY & 0xfc) << 2) | (MeLocX >> 3));
}
