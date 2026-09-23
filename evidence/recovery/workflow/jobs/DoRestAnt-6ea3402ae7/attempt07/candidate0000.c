/* DoRestAnt: validate the A-list coordinates and test the terrain-specific
 * nest tile. All failed checks share the zero result; successful nest checks
 * set the result once before the common dispatch. */
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
    int inNest;
    int code;

    x = AT(ant + 0x23a4) & 0xff;
    y = AT(ant + 0x278e);
    if (!IsValidA(x, y))
        goto not_in_nest;

    if (TERRAINset == 0) {
        if (MapA[x][y] != 0x50)
            goto not_in_nest;
    } else {
        code = MapA[x][y];
        if (code < 0x80 || code > 0x8f)
            goto not_in_nest;
    }
    inNest = 1;
    goto nest_result;

not_in_nest:
    inNest = 0;
nest_result:
    if (inNest == 1)
        GoInNest(x, y, ant);
    else if (SRand4() == 0)
        AT(ant + 0x2b78) = 2;
    else if (OptionStates[5] == 1)
        RestBalloons(x, y, 1);
}
