/*
 * ConnectAll refreshes the edited wall tile, followed in order by its
 * north, east, south, and west neighbors.  ConnectWall establishes the
 * four-neighbor wall test and the exact wallShape table; DropWall calls
 * ConnectAll after editing one MapA tile.  The shared linear cell index
 * mirrors the target's cached x*64+y base, and each adjacent cell is
 * bounds-checked before its map byte is read.
 */
extern unsigned char near MapA[8192];
extern int far GetMap(int plane, int x, int y);
extern int far IsValidA(int x, int y);

static unsigned char near wallShape[16] = {
    0x60, 0x64, 0x65, 0x66, 0x62, 0x61, 0x62, 0x61,
    0x63, 0x63, 0x60, 0x60, 0x67, 0x67, 0x67, 0x67
};

#define RECONNECT_BODY(cx, cy, delta) do { \
    cell = MapA[mapIndex + (delta)]; \
    isWall = (cell >= 0x60 && cell <= 0x67); \
    if (isWall) { \
        si = 0; \
        w = GetMap(1, (cx) - 1, (cy)); \
        ww = (w >= 0x60 && w <= 0x67); \
        if (ww == 1) si++; \
        si <<= 1; \
        w = GetMap(1, (cx), (cy) + 1); \
        ww = (w >= 0x60 && w <= 0x67); \
        if (ww == 1) si++; \
        si <<= 1; \
        w = GetMap(1, (cx) + 1, (cy)); \
        ww = (w >= 0x60 && w <= 0x67); \
        if (ww == 1) si++; \
        si <<= 1; \
        w = GetMap(1, (cx), (cy) - 1); \
        ww = (w >= 0x60 && w <= 0x67); \
        if (ww == 1) si++; \
        MapA[mapIndex + (delta)] = wallShape[si]; \
    } \
} while (0)

void far ConnectAll(int x, int y)
{
    int mapIndex;
    int cell;
    int isWall;
    int si;
    int w;
    int ww;
    int cx;
    int cy;

    mapIndex = (x << 6) + y;
    RECONNECT_BODY(x, y, 0);

    cy = y - 1;
    if (IsValidA(x, cy))
        RECONNECT_BODY(x, cy, -1);

    cx = x + 1;
    if (IsValidA(cx, y))
        RECONNECT_BODY(cx, y, 64);

    cy = y + 1;
    if (IsValidA(x, cy))
        RECONNECT_BODY(x, cy, 1);

    cx = x - 1;
    if (IsValidA(cx, y))
        RECONNECT_BODY(cx, y, -64);
}

#undef RECONNECT_BODY
