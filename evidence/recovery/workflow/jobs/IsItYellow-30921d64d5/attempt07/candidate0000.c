/*
 * IsItYellow reports whether the requested plane/tile shows yellow.  The
 * effective plane p is level (or 1 for level 0); the MePlane match is
 * materialized into a boolean "ok" (mov bx,1/jmp vs xor bx,bx, tested with
 * or/jne) rather than a direct conditional jump, matching the observed
 * shape.  When ok, a spider-lion special case (MeMode==1) tests Dist()
 * against the yellow radius for level<=1; otherwise a plain dense switch
 * on level selects LifeA/LifeB/LifeR and reports yellow for tile 0xff/0xfe.
 * level itself stays in cx/ax throughout, never copied to another local.
 */
extern int near MePlane;
extern int near SpidX;
extern int near SpidY;
extern int far MeMode;
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern long far Dist(int x1, int y1, int x2, int y2);

int far IsItYellow(int level, int x, int y)
{
    int p;
    int tile;

    if (level != 0)
        p = level;
    else
        p = 1;
    if (MePlane == p) {
        if (MeMode == 1) {
            if (level > 1)
                return 0;
            if (Dist(x * 16 + 8, y * 16 + 8, SpidX, SpidY) < 0x200)
                return 1;
            return 0;
        }
        switch (level) {
        case 0:
        case 1:
            tile = LifeA[x][y];
            break;
        case 2:
            tile = LifeB[x][y];
            break;
        case 3:
            tile = LifeR[x][y];
            break;
        }
        if (tile == 0xff || tile == 0xfe)
            return 1;
        return 0;
    }
    return 0;
}
