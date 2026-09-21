extern unsigned char far AlistY[];
extern unsigned char far AlistT[];
extern unsigned char far AlistX[];
extern unsigned char near LifeA[];
extern int near SRand1(unsigned int range);

void near SimEggA(int index)
{
    int y;
    int x;

    y = AlistY[index + 0x278e];
    x = AlistX[index + 0x23a4];
    LifeA[(x << 6) + y] = AlistT[index + 0x2f62];
    if (SRand1(0xc8)) {
        AlistT[index + 0x2f62] = 0;
        LifeA[(x << 6) + y] = 0;
    }
}
