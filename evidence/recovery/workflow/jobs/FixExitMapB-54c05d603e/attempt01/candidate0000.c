extern unsigned char near MapB[64][64];
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far ExitMapB[64][64];

void far FixExitMapB(int x, int y)
{
    int i;
    int nx;
    int ny;
    int value;
    int best;

    if (y < 2) {
        if (MapB[x][y] == 0x18)
            ExitMapB[x][y] = 0xff;
        else
            ExitMapB[x][y] = 0xfe;
        return;
    }
    best = 0;
    for (i = 0; i < 8; i++) {
        ny = Dy8[i] + y;
        nx = Dx8[i] + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        value = ExitMapB[nx][ny];
        if (value > best)
            best = value;
    }
    if (best)
        ExitMapB[x][y] = best - 1;
    else
        ExitMapB[x][y] = 0;
}
