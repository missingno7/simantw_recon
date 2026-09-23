/* Hypothesis: attack ants enter nest tiles first, otherwise use GetNestDir; terrain over Barrier causes a random turn, while a passable occupied cell triggers enemy combat derived from StartFightA. */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
extern int far IsValidA(int x, int y);
extern void near GoInNest(int x, int y, int index);
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern int far IsCarryCaste[];
extern int far UnCarryCaste[];
extern int far GetNestDir(int x, int y, int dir, int flag);
extern signed char far Dx8[];
extern signed char far Dy8[];
extern int far Barrier;
extern int far TERRAINset;
extern int far SRand8(void);
extern unsigned char far TurnTab[8][8];
extern int far IsYellowAnt(int ant);
extern int near MeColor;
extern void near YellowFight(int kind, int index);
extern int far FindInAList(int x, int y);
extern int near GetWinner(int defender, int attacker);
extern void near AlarmHere2(int x, int y, int level);

void near DoAttackAnt(int index)
{
    int x;
    int y;
    int type;
    int carry;
    int caste;
    int dir;
    int nx;
    int ny;
    int tile;
    int nextIndex;
    int other;
    int winner;

    x = AlistX[index];
    y = AlistY[index];
    type = AlistT[index] & 0xff;

    if (IsValidA(x, y)) {
        if (TERRAINset == 0) {
            if (MapA[(x << 6) + y] == 0x50) {
                GoInNest(x, y, index);
                return;
            }
        } else {
            tile = MapA[(x << 6) + y];
            if (tile >= 0x80 && tile <= 0x8f) {
                GoInNest(x, y, index);
                return;
            }
        }
    }

    caste = (type & 0x78) >> 3;
    if (IsCarryCaste[caste] == 1)
        carry = (UnCarryCaste[caste] << 3) | (type & 0x87);
    else
        carry = type;

    dir = GetNestDir(x, y, type & 7, type ^ 0x80);
    nx = x + Dx8[dir];
    ny = y + Dy8[dir];
    tile = MapA[(nx << 6) + ny];
    if (tile <= Barrier) {
        other = LifeA[(nx << 6) + ny];
        if (other == 0) {
            LifeA[(nx << 6) + ny] = (type & 0xf8) | dir;
            AlistT[index] = (type & 0xf8) | dir;
            AlistX[index] = nx;
            AlistY[index] = ny;
            return;
        }
        if (IsYellowAnt(other) == 1) {
            if (((type ^ MeColor) & 0x80) != 0) {
                YellowFight(1, index);
                return;
            }
            dir = SRand8();
            AlistT[index] = carry | TurnTab[type & 7][dir];
            MapA[(x << 6) + y] = AlistT[index];
            return;
        }
        if (((type ^ other) & 0x80) == 0) {
            dir = SRand8();
            AlistT[index] = carry | TurnTab[type & 7][dir];
            MapA[(x << 6) + y] = AlistT[index];
            return;
        }

        AlistT[index] = 0;
        LifeA[(x << 6) + y] = 0;
        nextIndex = FindInAList(nx, ny);
        if (nextIndex < 0)
            return;
        winner = GetWinner(AlistT[nextIndex], type);
        AlistT[nextIndex] = (winner & 0x80) + 0x70;
        LifeA[(nx << 6) + ny] = (winner & 0x80) + 0x70;
        AlistM[nextIndex] = 0xa;
        AlistS[nextIndex] = winner;
        AlarmHere2(nx, ny, 0x28);
        return;
    }

    dir = SRand8();
    AlistT[index] = carry | TurnTab[type & 7][dir];
    MapA[(x << 6) + y] = AlistT[index];
}


