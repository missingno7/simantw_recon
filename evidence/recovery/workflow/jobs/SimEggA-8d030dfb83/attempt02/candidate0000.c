extern unsigned char far Alist[];
extern unsigned char near LifeA[];
extern int far SRand1(unsigned int range);

void near SimEggA(int index)
{
    int y;
    int x;
    unsigned char type;

    y = Alist[index + 0x278e];
    type = Alist[index + 0x2f62];
    x = Alist[index + 0x23a4];
    LifeA[(x << 6) + y] = type;
    if (SRand1(0xc8)) {
        Alist[index + 0x2f62] = 0;
        LifeA[(x << 6) + y] = 0;
    }
}
