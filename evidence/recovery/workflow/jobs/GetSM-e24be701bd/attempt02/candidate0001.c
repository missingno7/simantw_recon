extern unsigned char far Dx8[];
extern signed char far ExpSubStates[];
#define SUBSTATE(i) ExpSubStates[i]

int far GetSM(int x, int y)
{
    int ok;
    int v;

    if (x >= 0 && x <= 0x3f)
        if (y >= 0 && y <= 0x1f)
            ok = 1;
        else
            ok = 0;
    else
        ok = 0;
    if (!ok)
        return -1;
    switch (SUBSTATE(5)) {
    case 0:
        v = Dx8[(x << 5) + y + 0x62d2];
        break;
    case 1:
        v = Dx8[(x << 5) + y + 0x6ad2];
        break;
    case 2:
        v = Dx8[(x << 5) + y + 0x72d2];
        break;
    case 3:
        v = Dx8[(x << 5) + y + 0x7ad2];
        break;
    case 4:
        v = Dx8[(x << 5) + y + 0x52d2];
        break;
    }
    return v;
}
