/*
 * GetMowDir: pick a direction toward an unmowed neighbour square around
 * the yard position (x, y). Tries the four compass offsets from the
 * private mowDx/mowDy delta tables (N, E, S, W; read from the game's
 * own initialized DGROUP bytes at DS:0x25D4/0x25D8: 0,1,0,-1 and
 * -1,0,1,0) starting at index 3 down to 0. A candidate square must land
 * inside the 12-wide (0..0xb) by 16-tall (0..0xf) mow-position grid
 * (the four-way test is kept in a boolean local, which the compiler
 * materialises in DX); the first candidate whose match_position bit is
 * still set is claimed (bit cleared, NotMowed's idiom, with the claim
 * result kept in a second boolean local materialised in BX) and its
 * direction index is returned. If no direction is claimed: an
 * out-of-range x (>10) returns 0, an out-of-range y (>14) returns 1,
 * and a y below 1 schedules the kid's mow-me message (300 ticks out,
 * offset 6) and marks the boy present (BoyHere=4), returning 2;
 * otherwise the current YardCycle's low two bits are returned.
 *
 * Register evidence (agentX, og profile of simtwo:1378): the boolean
 * locals reproduce the target's mov dx,1/xor dx,dx/or dx,dx and
 * mov bx,1/xor bx,bx/or bx,bx materialisations, the mask lives in AX
 * with an unused home ([bp-2], enter 4), i in [bp-4], and the ES
 * selector load is hoisted out of the loop (90/92 aligned opcodes).
 * Remaining difference: the target computes cx into SI before cy into
 * DI and tests cx with or si,si, while MSC 7 here sinks the first-tested
 * cx below cy and tests it with js (cy takes SI); declaration, table,
 * statement and name orders do not move it.
 */
extern int far match_position[];
extern unsigned long far BoyMsgCnt;
extern int far BoyMessOn;
extern int far BoyMsgOffset;
extern int near BoyHere;
extern int far YardCycle;
extern unsigned long far MacTickCount(void);

static signed char near mowDx[4] = { 0, 1, 0, -1 };
static signed char near mowDy[4] = { -1, 0, 1, 0 };

int far GetMowDir(int x, int y)
{
    int i, cx, cy, ok, mask, found;

    for (i = 3; i >= 0; i--) {
        cx = mowDx[i] + x;
        cy = mowDy[i] + y;
        ok = cx >= 0 && cy >= 0 && cx <= 0xb && cy <= 0xf;
        if (ok) {
            mask = 1 << cy;
            if (match_position[cx] & mask) {
                match_position[cx] -= mask;
                found = 1;
            } else
                found = 0;
            if (found)
                return i;
        }
    }

    if (x > 10)
        return 0;
    if (y > 14)
        return 1;
    if (y < 1) {
        BoyMsgCnt = MacTickCount() + 300L;
        BoyMessOn = 1;
        BoyMsgOffset = 6;
        BoyHere = 4;
        return 2;
    }
    return YardCycle & 3;
}
