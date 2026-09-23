/*
 * DoRestAnt: let a resting A-list ant act.  Its position comes from the
 * list (row at Dx8 offset 0x23a4 read as a masked word, column at 0x278e).
 * The ant is "in the nest" when its cell is valid and, with the standard
 * terrain (TERRAINset 0), the MapA cell is the nest code 0x50, or with a
 * custom terrain the code lies in 0x80..0x8f.  In the nest it goes in
 * (GoInNest); otherwise a random chance (SRand4 zero) puts it back to
 * mode 2 (0x2b78), and if option 5 is on it shows rest balloons instead.
 * The list bytes share one selector slot (far byte addressed by offset).
 */
extern unsigned char near MapA[128][64];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
extern int far TERRAINset;
extern int far OptionStates[];

extern int far IsValidA(int x, int y);
extern void far GoInNest(int x, int y, int index);
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
        inNest = 0;
    else if (TERRAINset == 0)
        inNest = MapA[x][y] == 0x50;
    else {
        code = MapA[x][y];
        inNest = code >= 0x80 && code <= 0x8f;
    }
    if (inNest == 1)
        GoInNest(x, y, ant);
    else if (SRand4() == 0)
        AT(ant + 0x2b78) = 2;
    else if (OptionStates[5] == 1)
        RestBalloons(x, y, 1);
}
