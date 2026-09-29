/*
 * ConnectAll refreshes the edited wall tile, followed in order by its
 * north, east, south, and west neighbors.  ConnectWall establishes the
 * four-neighbor wall test and the exact wallShape table; DropWall calls
 * ConnectAll after editing one MapA tile.  The shared linear cell index
 * mirrors the target's cached x*64+y base, and each adjacent cell is
 * bounds-checked before its map byte is read.
 */
extern unsigned char near MapA[];
extern int far GetMap(int plane, int x, int y);
extern int far IsValidA(int x, int y);

static unsigned char near wallShape[16] = {
    0x60, 0x64, 0x65, 0x66, 0x62, 0x61, 0x62, 0x61,
    0x63, 0x63, 0x60, 0x60, 0x67, 0x67, 0x67, 0x67
};

#define RECONNECT_BODY(tx, ty, delta, lx, ly, dx, dy, rx, ry, ux, uy) do { \
    cell = MapA[mapIndex + (delta)]; \
    isWall = (cell >= 0x60 && cell <= 0x67); \
    if (isWall) { \
        mask = 0; \
        w = GetMap(1, (lx), (ly)); \
        ww = (w >= 0x60 && w <= 0x67); \
        if (ww == 1) (mask)++; \
        mask <<= 1; \
        w = GetMap(1, (dx), (dy)); \
        ww = (w >= 0x60 && w <= 0x67); \
        if (ww == 1) (mask)++; \
        mask <<= 1; \
        w = GetMap(1, (rx), (ry)); \
        ww = (w >= 0x60 && w <= 0x67); \
        if (ww == 1) (mask)++; \
        mask <<= 1; \
        w = GetMap(1, (ux), (uy)); \
        ww = (w >= 0x60 && w <= 0x67); \
        if (ww == 1) (mask)++; \
        MapA[mapIndex + (delta)] = wallShape[mask]; \
    } \
} while (0)

void far ConnectAll(int x, int y)
{
    int mapIndex;
    int cell;
    int isWall;
    int mask;
    int w;
    int ww;
    int neighbor[4];

    mapIndex = (x << 6) + y;
    RECONNECT_BODY(x, y, 0, x - 1, y, x, y + 1, x + 1, y, x, y - 1);

    neighbor[0] = y - 1;
    if (IsValidA(x, neighbor[0]))
        RECONNECT_BODY(x, neighbor[0], -1, x - 1, neighbor[0], x, y, x + 1, neighbor[0], x, y - 2);

    neighbor[1] = x + 1;
    if (IsValidA(neighbor[1], y))
        RECONNECT_BODY(neighbor[1], y, 64, x, y, neighbor[1], y + 1, neighbor[1] + 1, y, neighbor[1], neighbor[0]);

    neighbor[2] = y + 1;
    if (IsValidA(x, neighbor[2]))
        RECONNECT_BODY(x, neighbor[2], 1, x - 1, neighbor[2], x, neighbor[2] + 1, neighbor[1], neighbor[2], x, y);

    neighbor[3] = x - 1;
    if (IsValidA(neighbor[3], y))
        RECONNECT_BODY(neighbor[3], y, -64, neighbor[3] - 1, y, neighbor[3], neighbor[2], x, y, neighbor[3], neighbor[0]);
}

#undef RECONNECT_BODY
