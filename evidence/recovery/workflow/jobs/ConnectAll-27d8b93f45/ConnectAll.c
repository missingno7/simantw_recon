/*
 * ConnectAll recomputes the wall-shape entry for the edited map cell and
 * its four orthogonal neighbors.  The center is already validated by its
 * caller; neighboring cells are gated by IsValidA.  Each cell uses the
 * same four-neighbor mask and table proven for ConnectWall.
 */
extern unsigned char near MapA[][64];
extern int far GetMap(int plane, int x, int y);
extern int far IsValidA(int x, int y);

static unsigned char near wallShape[16] = {
    0x60, 0x64, 0x65, 0x66, 0x62, 0x61, 0x62, 0x61,
    0x63, 0x63, 0x60, 0x60, 0x67, 0x67, 0x67, 0x67
};

#define RECONNECT_CELL(cx, cy, validate) do { \
    int wall_x = (cx); \
    int wall_y = (cy); \
    if (!(validate) || IsValidA(wall_x, wall_y)) { \
        unsigned char near *cellPtr; \
        int cell; \
        int isWall; \
        int si; \
        int w; \
        int ww; \
        cellPtr = &MapA[wall_x][wall_y]; \
        cell = *cellPtr; \
        isWall = (cell >= 0x60 && cell <= 0x67); \
        if (isWall) { \
            si = 0; \
            w = GetMap(1, wall_x - 1, wall_y); \
            ww = (w >= 0x60 && w <= 0x67); \
            if (ww == 1) si++; \
            si <<= 1; \
            w = GetMap(1, wall_x, wall_y + 1); \
            ww = (w >= 0x60 && w <= 0x67); \
            if (ww == 1) si++; \
            si <<= 1; \
            w = GetMap(1, wall_x + 1, wall_y); \
            ww = (w >= 0x60 && w <= 0x67); \
            if (ww == 1) si++; \
            si <<= 1; \
            w = GetMap(1, wall_x, wall_y - 1); \
            ww = (w >= 0x60 && w <= 0x67); \
            if (ww == 1) si++; \
            *cellPtr = wallShape[si]; \
        } \
    } \
} while (0)

void far ConnectAll(int x, int y)
{
    RECONNECT_CELL(x, y, 0);
    RECONNECT_CELL(x, y - 1, 1);
    RECONNECT_CELL(x + 1, y, 1);
    RECONNECT_CELL(x, y + 1, 1);
    RECONNECT_CELL(x - 1, y, 1);
}

#undef RECONNECT_CELL
