/* DoRestAnt: get this ant's row and column from the A-list. If the valid
 * tile is the nest for the current terrain, send the ant into the nest and
 * return. Otherwise a zero SRand4 result changes its mode to 2; a nonzero
 * result may show the rest balloons when option 5 is enabled. */
extern unsigned char near MapA[128][64];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
extern int far TERRAINset;
extern int far OptionStates[];
extern int far IsValidA(int x, int y);
extern void near GoInNest(int x, int y, int ant);
extern int far SRand4(void);
extern void far RestBalloons(int x, int y, int kind);

void near DoRestAnt(int ant)
{
    int x;
    int y;
    int code;

    x = AT(ant + 0x23a4) & 0xff;
    y = AT(ant + 0x278e);

    if (IsValidA(x, y)) {
        if (TERRAINset == 0) {
            if (MapA[x][y] == 0x50) {
                GoInNest(x, y, ant);
                return;
            }
        } else {
            code = MapA[x][y];
            if (code >= 0x80 && code <= 0x8f) {
                GoInNest(x, y, ant);
                return;
            }
        }
    }

    if (SRand4() == 0) {
        AT(ant + 0x2b78) = 2;
        return;
    }
    if (OptionStates[5] == 1)
        RestBalloons(x, y, 1);
}
