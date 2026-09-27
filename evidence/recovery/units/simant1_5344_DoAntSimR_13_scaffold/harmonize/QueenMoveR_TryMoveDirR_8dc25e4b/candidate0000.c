struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};

extern struct RListPlanes far RlistX;
extern int far TileMassXR;
extern int far TileMassYR;
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char near LifeR[];
extern int near GetBestDir(int kind, int x, int y, int targetX, int targetY);
extern int far SRand8(void);
extern int far TryMoveDirR(int x, int y, int dir);
extern int far FindInRList(int x, int y, int ant);

int far QueenMoveR(int x, int y, int dirHint)
{
    int dir;
    int newRow;
    int newCol;
    int opp;
    int index;

    dir = GetBestDir(3, x, y, TileMassXR, TileMassYR);
    if (dir < 0) {
        dir++;
        if (dir == 0)
            return 0;
        dir = SRand8();
    }
    if (y < 3) {
        if (dir > 5)
            return 0;
        if (dir < 3)
            return 0;
    }
    if (TryMoveDirR(x, y, dir) != 0) {
        opp = (dirHint ^ 0xfc) & 7;
        newCol = x + Dx8[opp];
        newRow = y + Dy8[opp + 8];
        LifeR[newCol * 64 + newRow] = 0;

        index = FindInRList(newCol, newRow, (dirHint & 7) + 0xe8);
        if (index >= 0 && RlistX.t[index] != 0) {
            RlistX.x[index] = (char)x;
            RlistX.y[index] = (char)y;
            RlistX.t[index] = (char)(dir - 0x18);
            LifeR[x * 64 + y] = (unsigned char)(dir - 0x18);
        }
        return 1;
    }
    return 0;
}
