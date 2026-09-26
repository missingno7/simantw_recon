/* R mirror: one aggregate fixes best, bestValue, and back homes in order. */
extern unsigned char far ExitMapR[64][64];
#define EXITMAP(x,y) ExitMapR[x][y]
extern char far Dx8[];
extern char far Dy8[];
extern int far SRand2(void);
struct ChoiceState { int best; int bestValue; int back; };
int far GetEnterDirR(int x, int y, int dir)
{
    struct ChoiceState state;
    int i, nx, ny, value;
    state.back = dir ^ 4;
    state.best = -1;
    state.bestValue = EXITMAP(x,y);
    for (i = 0; i < 8; ++i) {
        if (state.back == i) continue;
        ny = Dy8[i] + y;
        nx = Dx8[i] + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63) continue;
        value = EXITMAP(nx,ny);
        if (value == 0) continue;
        if (state.bestValue < value) continue;
        if (state.bestValue <= value && SRand2() == 0) continue;
        state.bestValue = value;
        state.best = i;
    }
    return state.best;
}
