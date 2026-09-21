extern unsigned char far Alist[];
extern unsigned char near LifeA[];
extern int far SRand1(unsigned int range);

void near SimEggA(int index)
{
    int y;
    int x;

    y = Alist[index + 0x278e];
    x = Alist[index + 0x23a4];
    LifeA[(x << 6) + y] = Alist[index + 0x2f62];
    if (!SRand1(0xc8)) {
        Alist[index + 0x2f62] = 0;
        LifeA[(x << 6) + y] = 0;
    }
}
