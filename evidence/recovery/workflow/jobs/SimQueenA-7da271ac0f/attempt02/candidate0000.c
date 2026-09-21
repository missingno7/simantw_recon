/*
 * SimQueenA: simulate an A-list queen-type ant.  The ant's type byte
 * (list offset 0x2f62) is written into its LifeA cell (row 0x23a4,
 * column 0x278e).  For queen codes (type & 0x7f above 0x67) the cell one
 * step ahead in the type's low-three-bit direction is examined: unless
 * it holds the matching code eight below the type, and no listed ant is
 * found there, the queen is removed from the map and the list.  The
 * list bytes share one selector slot (far byte addressed by offset).
 */
extern unsigned char near LifeA[128][64];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
extern char far Dy8[];
#define DY(i) Dy8[i]
#define DX(i) ((char)(&Dx8)[i])
extern int far FindInAList(int x, int y);

void near SimQueenA(int ant)
{
    int x;
    int y;
    int type;
    int nx;
    int ny;
    int dead;
    unsigned char far *rec;

    rec = &Dx8 + ant;
    y = rec[0x278e] & 0xff;
    type = rec[0x2f62];
    x = rec[0x23a4];
    LifeA[x][y] = type;
    if ((type & 0x7f) > 0x67) {
        ny = DY(type & 7) + y;
        nx = DX(type & 7) + x;
        dead = LifeA[nx][ny] - type != -8 && FindInAList(nx, ny) < 0;
        if (dead) {
            LifeA[x][y] = 0;
            AT(ant + 0x2f62) = 0;
        }
    }
}
