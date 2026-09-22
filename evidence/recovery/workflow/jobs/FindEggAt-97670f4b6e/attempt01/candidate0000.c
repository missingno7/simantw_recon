/*
 * FindEggAt (SIMONE_MODULE, unit simone:5AD2, profile "og"; my ant
 * object). Same shape and same LifeA/LifeB/LifeR/ListIndexA/B/R bindings
 * as _FindLifeAt (confirmed by identical calls list and identical
 * direct_data_bindings in this packet) -- see that candidate's notes for
 * the unresolved coordinate-validation/mask-selection prelude. The one
 * confirmed difference from _FindLifeAt: the FindLifeIndex call's "high"
 * constant is 7 here (push 0x7f; push 7; push 1) instead of 0x7f,
 * narrowing the accepted attribute range to [1,7] -- consistent with
 * selecting an egg-only attribute band rather than the broader default.
 * This is a best-effort, lower-confidence first pass capturing only the
 * well-evidenced tail (FindLifeIndex + GetAntIndex calls and the far
 * out-parameter store), exactly as with _FindLifeAt.
 */

extern int far FindLifeIndex(int list, int matchLife, int matchColumn, int low, int high, int mask);
extern int far GetAntIndex(int list, int index, int far *life, int far *column,
                            int far *attribute, int far *state, int far *direction);

int far FindEggAt(int far *outIndex, int p1, int x, int y)
{
    int list;
    int idx;
    int life;
    int column;
    int attribute;
    int state;
    int direction;

    list = p1;
    idx = FindLifeIndex(list, x, y, 1, 7, 0x7f);
    if (idx < 0) {
        *outIndex = -1;
        return -1;
    }

    GetAntIndex(list, idx, &life, &column, &attribute, &state, &direction);
    *outIndex = idx;
    return life;
}
