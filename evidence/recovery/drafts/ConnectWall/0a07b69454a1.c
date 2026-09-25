/*
 * ConnectWall: after placing a wall tile at map cell (x,y), pick its
 * connected wall-shape sprite from the 4 orthogonal neighbours via
 * GetMap(1,...).  If the cell itself isn't a wall tile (0x60-0x67) do
 * nothing.  Otherwise build a 4-bit neighbour mask (west*8+south*4+
 * east*2+north, set per wall neighbour) and store the private
 * wall-shape table's byte for that mask back into the map cell.
 */
extern unsigned char near MapA[][64];
extern int far GetMap(int plane, int x, int y);

static unsigned char near wallShape[16] = {
    0x60, 0x64, 0x65, 0x66, 0x62, 0x61, 0x62, 0x61,
    0x63, 0x63, 0x60, 0x60, 0x67, 0x67, 0x67, 0x67
};

void far ConnectWall(int x, int y)
{
    int w;
    int ww;
    int si;
    int cell;
    int isWall;
    unsigned char near *cellPtr;

    cellPtr = &MapA[x][y];
    cell = *cellPtr;
    isWall = (cell >= 0x60 && cell <= 0x67);
    if (isWall) {
        si = 0;

        w = GetMap(1, x - 1, y);
        ww = (w >= 0x60 && w <= 0x67);
        if (ww == 1)
            si++;
        si <<= 1;

        w = GetMap(1, x, y + 1);
        ww = (w >= 0x60 && w <= 0x67);
        if (ww == 1)
            si++;
        si <<= 1;

        w = GetMap(1, x + 1, y);
        ww = (w >= 0x60 && w <= 0x67);
        if (ww == 1)
            si++;
        si <<= 1;

        w = GetMap(1, x, y - 1);
        ww = (w >= 0x60 && w <= 0x67);
        if (ww == 1)
            si++;

        *cellPtr = wallShape[si];
    }
}
