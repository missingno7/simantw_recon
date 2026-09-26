/*
 * DoRandAntA: one simulation step for a wandering ant in the A list.
 * The ant's cell (x, y) and type byte t come from AlistX/AlistY/AlistT.
 * If the cell is a valid nest tile (0x50 in the default TERRAINset, else
 * 0x80..0x8f), the ant goes into the nest.  Otherwise it picks a random
 * direction for its kind (t & 7) and looks at the neighbouring tile
 * (x + Dx8[dir], y + Dy8[dir]).  Food there (IsItFood band by TERRAINset)
 * makes a forager (mode 2 or 6) pick it up and start carrying (mode 3,
 * stamina 0xc8).  A tile above Barrier turns the ant using TurnTab.  An
 * empty LifeA cell moves the ant there, lays its colony's scent trail while
 * stamina lasts, decays the trail smell and, on a zero random draw, sends a
 * forager home (mode 2).  A yellow occupant is fought (YellowFight) when the
 * colours differ, otherwise fed by trophallaxis when wanted, then the ant
 * turns.  A same-colour occupant turns the ant and asks GetNewMode for a
 * new mode.  An enemy occupant fights: the loser found by FindInAList gets
 * the GetWinner result as colour 0x70/0xf0, mode 0xa and stamina, and an
 * alarm is raised at the cell.
 *
 * Declarations: the five Alist byte arrays share one CONST selector slot
 * (0xc318) in the original, while Dx8/Dy8 (signed direction tables at
 * SIMANT_DATA_GROUP 0 and 8), TERRAINset, Barrier, TurnTab and MeWantFood
 * each use their own slots 0xc31c..0xc330 with gaps; these are recorded as
 * translation-unit layout evidence.  MapA, LifeA and MeColor are near
 * DGROUP objects.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
extern char far Dx8[];
extern char far Dy8[];
extern char far TurnTab[8][8];
extern int far TERRAINset;
extern int far Barrier;
extern int far MeWantFood;
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern unsigned char near MeColor;

extern int far IsValidA(int x, int y);
extern void near GoInNest(int x, int y, int ant);
extern int far GetRandDir(int x, int y, int kind);
extern void far PickupFoodA(int x, int y);
extern int far SRand8(void);
extern int far IsYellowAnt(int value);
extern void near YellowFight(int how, int ant);
extern void far DoTroph(int x, int y, int dir);
extern int far GetNewMode(int mode, int type);
extern int far FindInAList(int x, int y);
extern int near GetWinner(int defender, int attacker);
extern void near JamScentRN(int x, int y, int scent);
extern void near JamScentBN(int x, int y, int scent);
extern void near DecTSmell(int x, int y, int red);
extern void near AlarmHere2(int x, int y, int level);

#define IS_NEST(tile) (TERRAINset == 0 ? (tile) == 0x50 : ((tile) >= 0x80 && (tile) <= 0x8f))
#define IS_FOOD(tile) (TERRAINset == 0 ? ((tile) >= 0x48 && (tile) <= 0x4b) : ((tile) >= 0x18 && (tile) <= 0x27))

void near DoRandAntA(int ant)
{
    int antIndex;
    int t;
    int tile;
    int oldX;
    int colour;
    int dir;
    int y;
    int nx;
    int ny;
    int mode;
    int kind;
    unsigned char near *cell;
    int x;
    int inNest;
    int other;
    int loser;
    int winner;

    antIndex = ant;
    x = AlistX[antIndex];
    y = AlistY[antIndex];
    t = AlistT[antIndex];
    inNest = 0;
    if (!IsValidA(x, y))
        goto nest_check;
    if (TERRAINset == 0) {
        if (MapA[x * 64 + y] == 0x50)
            inNest = 1;
    } else {
        tile = MapA[x * 64 + y];
        if (tile >= 0x80 && tile <= 0x8f)
            inNest = 1;
    }
nest_check:
    if (inNest) {
        GoInNest(x, y, ant);
        return;
    }
    colour = t & 0xf8;
    mode = (t & 0x78) >> 3;
    kind = t & 7;
    dir = GetRandDir(x, y, kind);
    nx = x + Dx8[dir];
    ny = y + Dy8[dir];
    tile = MapA[nx * 64 + ny];
    if (IS_FOOD(tile) == 1) {
        if (mode == 6 || mode == 2) {
            AlistT[antIndex] = LifeA[x * 64 + y] = dir | colour | 8;
            AlistM[antIndex] = 3;
            PickupFoodA(nx, ny);
            AlistS[antIndex] = 0xc8;
            return;
        }
    } else if (Barrier < tile) {
        AlistT[antIndex] = LifeA[x * 64 + y] = TurnTab[kind][SRand8()] | colour;
        return;
    }
    cell = &LifeA[nx * 64 + ny];
    other = *cell;
    if (other == 0) {
        *cell = AlistT[antIndex] = dir | colour;
        LifeA[x * 64 + y] = 0;
        AlistX[antIndex] = nx;
        AlistY[antIndex] = ny;
        if (AlistS[antIndex] != 0) {
            AlistS[antIndex]--;
            if (t & 0x80)
                JamScentRN(nx, ny, AlistS[antIndex]);
            else
                JamScentBN(nx, ny, AlistS[antIndex]);
        }
        DecTSmell(nx, ny, t & 0x80);
        if (SRand8() == 0) {
            if (mode == 6 || mode == 2)
                AlistM[antIndex] = 2;
        }
        return;
    }
    oldX = x;
    if (IsYellowAnt(other) == 1) {
        if ((t ^ MeColor) & 0x80) {
            YellowFight(1, ant);
            return;
        }
        if (MeWantFood == 1) {
            AlistT[antIndex] = LifeA[oldX * 64 + y] = dir | colour;
            DoTroph(oldX, y, dir);
        }
        AlistT[antIndex] = LifeA[oldX * 64 + y] = TurnTab[kind][SRand8()] | colour;
        return;
    }
    if (((other ^ t) & 0x80) == 0) {
        AlistT[antIndex] = LifeA[oldX * 64 + y] = TurnTab[kind][SRand8()] | colour;
        AlistM[antIndex] = GetNewMode(mode, t);
        return;
    }
    t = AlistT[antIndex];
    AlistT[antIndex] = 0;
    LifeA[oldX * 64 + y] = 0;
    loser = FindInAList(nx, ny);
    if (loser < 0)
        return;
    winner = GetWinner(AlistT[loser], t);
    AlistT[loser] = *cell = (winner & 0x80) + 0x70;
    AlistM[loser] = 0xa;
    AlistS[loser] = winner;
    AlarmHere2(nx, ny, 0x28);
}
