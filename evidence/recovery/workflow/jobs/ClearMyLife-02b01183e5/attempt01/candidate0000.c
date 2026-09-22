/*
 * ClearMyLife: undo SetLife's occupancy marks for an ant at (plane, x, y)
 * facing dir, called first thing by the admitted MoveMyLife (src/
 * recovered/wf_MoveMyLife-f66a8c0d06.c) before it writes the new
 * position.  The current cell's occupancy byte (LifeA/LifeB/LifeR, same
 * arrays and bounds idiom used throughout this unit) is read through
 * IsValidLocation; a stale self marker (0xff) is cleared via SetLife(...,
 * 0), and the cell is always repainted with ZapEuMapAt.  A queen (type
 * 0x60) also clears the trailing segment cell behind her, at the reverse
 * direction dir^4 through the far Dx8/Dy8 step tables (char deltas, the
 * same tables MoveMyLife uses to mark 0xfe there); that cell's stale
 * marker is 0xfe rather than 0xff.
 */
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern char far Dy8[];
extern char far Dx8[];

extern int far IsValidLocation(int plane, int x, int y);
extern void far SetLife(int plane, int x, int y, int code);
extern void far ZapEuMapAt(int plane, int x, int y);

#define TRUE 1
#define FALSE 0

void far ClearMyLife(int plane, int x, int y, int type, int dir)
{
    int ok;
    int val;
    int tailX;
    int tailY;

    if (plane <= 1)
        ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (ok == TRUE) {
        val = -1;
        if (IsValidLocation(plane, x, y) == TRUE) {
            switch (plane) {
            case 0:
            case 1:
                val = LifeA[x][y];
                break;
            case 2:
                val = LifeB[x][y];
                break;
            case 3:
                val = LifeR[x][y];
                break;
            }
            if (val == 0)
                val = -1;
        }
        if (val == 0xff)
            SetLife(plane, x, y, 0);
        ZapEuMapAt(plane, x, y);
    }

    if (type != 0x60)
        return;

    tailX = x + Dx8[dir ^ 4];
    tailY = y + Dy8[dir ^ 4];

    if (plane <= 1)
        ok = (tailX >= 0 && tailX <= 0x7f && tailY >= 0 && tailY <= 0x3f);
    else
        ok = (tailX >= 0 && tailX <= 0x3f && tailY >= 0 && tailY <= 0x3f);
    if (ok == FALSE)
        return;

    val = -1;
    if (IsValidLocation(plane, tailX, tailY) == TRUE) {
        switch (plane) {
        case 0:
        case 1:
            val = LifeA[tailX][tailY];
            break;
        case 2:
            val = LifeB[tailX][tailY];
            break;
        case 3:
            val = LifeR[tailX][tailY];
            break;
        }
        if (val == 0)
            val = -1;
    }
    if (val == 0xfe)
        SetLife(plane, tailX, tailY, 0);
    ZapEuMapAt(plane, tailX, tailY);
}
