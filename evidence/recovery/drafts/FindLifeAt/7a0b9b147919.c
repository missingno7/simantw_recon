/*
 * FindLifeAt (SIMONE_MODULE, unit simone:5AD2, profile "og"; my ant
 * object). This is a best-effort, lower-confidence first pass: the
 * function is large (473 bytes) with an intricate coordinate-validation
 * and mask-selection prelude (bounds-checking di/cx against 128x64 or
 * 64x64, then reading LifeA/LifeB/LifeR[di][cx] as a "mask" byte depending
 * on which of four sub-modes p1 selects) that has not been fully verified
 * here; only the well-evidenced tail is captured precisely: it calls the
 * already-admitted FindLifeIndex(list, matchLife, matchColumn, low, high,
 * mask) (src/recovered/wf_FindLifeIndex-3b1fa0607c.c) and, on success,
 * GetAntIndex(list, index, &life, &column, &attribute, &state, &direction)
 * (src/recovered/wf_GetAntIndex-a8eba5e594.c) with five local out
 * parameters (matching the five "lea ax,[bp-N];push ss;push ax" argument
 * pushes seen in the disassembly), stores the found index through the far
 * out-parameter and returns the life value (or -1 / stores -1 on failure).
 * LifeA/LifeB/LifeR and ListIndexA/B/R are confirmed by exact MAPSYM
 * bindings but this candidate does not yet reproduce their exact use.
 */

extern int far FindLifeIndex(int list, int matchLife, int matchColumn, int low, int high, int mask);
extern int far GetAntIndex(int list, int index, int far *life, int far *column,
                            int far *attribute, int far *state, int far *direction);

int far FindLifeAt(int far *outIndex, int p1, int x, int y)
{
    int list;
    int idx;
    int life;
    int column;
    int attribute;
    int state;
    int direction;

    list = p1;
    idx = FindLifeIndex(list, x, y, 1, 0x7f, 0x7f);
    if (idx < 0) {
        *outIndex = -1;
        return -1;
    }

    GetAntIndex(list, idx, &life, &column, &attribute, &state, &direction);
    *outIndex = idx;
    return life;
}
