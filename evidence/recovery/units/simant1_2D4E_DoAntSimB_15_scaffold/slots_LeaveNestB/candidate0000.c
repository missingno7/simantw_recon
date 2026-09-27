/* Selector identity probe: use the BlistX base for the shared B-list fields. */
struct BListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct BListPlanes far BlistX;

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
extern unsigned char near LifeB[128][64];



extern unsigned char far HoleMapB[];
extern int far Tindex;

extern void far MakeNewHoleB(int x);
extern int far SRand8(void);
extern int far ExitHole(int hole, int x, int dir, int mode, int state);

int far LeaveNestB(int x, int y)
{
    int dir;

    dir = BlistX.t[Tindex];
    BlistX.t[Tindex] = 0;
    if (HoleMapB[x] == 0)
        MakeNewHoleB(x);
    if (ExitHole(HoleMapB[x], x, SRand8() + (dir & 0xf8), BlistX.m[Tindex], BlistX.s[Tindex])) {
        LifeB[x][y] = 0;
        return 1;
    }
    BlistX.t[Tindex] = dir;
    BlistX.m[Tindex] = 0;
    return 0;
}
