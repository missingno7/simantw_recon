extern unsigned char far Dx8[];
extern unsigned char far ExpSubStates[];
#define SUBSTATE(i) ExpSubStates[i]

void far SetSM(int x, int y, int val)
{
    int ok;

    if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x1f)
        ok = 1;
    else
        ok = 0;
    if (ok) {
        if (val > 0xff)
            val = 0xff;
        switch (SUBSTATE(5)) {
        case 0:
            Dx8[(x << 5) + y + 0x62d2] = val;
            break;
        case 1:
            Dx8[(x << 5) + y + 0x6ad2] = val;
            break;
        case 2:
            Dx8[(x << 5) + y + 0x72d2] = val;
            break;
        case 3:
            Dx8[(x << 5) + y + 0x7ad2] = val;
            break;
        case 4:
            Dx8[(x << 5) + y + 0x52d2] = val;
            break;
        }
    }
}
