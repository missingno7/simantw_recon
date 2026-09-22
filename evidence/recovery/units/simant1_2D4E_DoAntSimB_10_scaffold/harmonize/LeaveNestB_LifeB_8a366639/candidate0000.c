/*
 * LeaveNestB: the current black ant (Tindex) tries to leave the nest at
 * surface cell (x, y).  Its list type byte is saved and cleared; if the
 * hole map has no hole there one is dug (MakeNewHoleB).  ExitHole is then
 * asked to place the ant outside using a random 8-way heading combined
 * with the saved type's high bits, plus the ant's mode and state bytes.
 * On success the LifeB cell is cleared and 1 is returned; otherwise the
 * saved type is restored, the mode byte cleared, and 0 returned.
 * BlistT/BlistM/BlistS share one far selector (Dx8 object, addressed by
 * offset); HoleMapB and Tindex are separate far objects.
 */
extern unsigned char near LifeB[];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define BlistT(i) AT((i) + 0x3d18)
#define BlistS(i) AT((i) + 0x3f0e)
#define BlistM(i) AT((i) + 0x3b22)
extern unsigned char far HoleMapB[];
extern int far Tindex;

extern void far MakeNewHoleB(int x);
extern int far SRand8(void);
extern int far ExitHole(int hole, int x, int dir, int mode, int state);

int far LeaveNestB(int x, int y)
{
    int dir;

    dir = BlistT(Tindex);
    BlistT(Tindex) = 0;
    if (HoleMapB[x] == 0)
        MakeNewHoleB(x);
    if (ExitHole(HoleMapB[x], x, SRand8() + (dir & 0xf8), BlistM(Tindex), BlistS(Tindex))) {
        LifeB[x][y] = 0;
        return 1;
    }
    BlistT(Tindex) = dir;
    BlistM(Tindex) = 0;
    return 0;
}
