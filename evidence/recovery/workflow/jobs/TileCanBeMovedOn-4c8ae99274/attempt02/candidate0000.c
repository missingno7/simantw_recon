/*
 * TileCanBeMovedOn: whether an ant currently at (curPlane, curX, curY) can
 * move onto (plane, x, y).
 *
 * Surface planes 0/1 (bounds 0<=x<=0x7f, 0<=y<=0x3f) are a plain terrain
 * check against MapA: the TERRAINset band selector (PACK:9B6E, same named
 * far word as src/recovered/IsNotBarrier.c / IsLessThanHole.c /
 * wf_IsItFood-c02f58780a.c) raises the walkable ceiling from 0x53 to
 * 0x90 while it is set, and the result returns immediately.
 *
 * Underground planes 2/3 (bounds 0<=x<=0x3f, 0<=y<=0x3f) read MapB/MapR.
 * A tile at or below 0x18, or in the pebble range 0x30-0x31 (the same
 * pebble range as the admitted IsLiftable), is already open (no digging
 * needed).  A dirt tile in 0x1c-0x2e is passable only when the mover
 * can dig, and then needs digging.  Anything else is impassable.
 *
 * A passable underground tile is only actually reachable from row 0 or
 * 1 and only on the mover's own plane.  Without digging gear, only row 0
 * qualifies, and only when the mover is already lined up on x and not
 * already standing on the same cell.  With digging gear on a tile that
 * needed no digging, any row qualifies outright once off row 0, and row
 * 0 uses the same lined-up-on-x test.  With digging gear on a tile that
 * did need digging, the move is allowed once the mover is lined up on x;
 * off row 0 it additionally requires that the tile directly "north"
 * (y+1) of the target is not itself diggable dirt (0x20-0x2e), i.e. the
 * ceiling above the dig site must already be open or solid rock.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far TERRAINset;

int far TileCanBeMovedOn(int plane, int x, int y, int curPlane, int curX, int curY, int canDig)
{
    int tile;
    int needsDig;
    int result;
    int ok;

    if (plane <= 1) {
        if (x < 0)
            goto badpos;
        if (x > 0x7f)
            goto badpos;
        if (y < 0)
            goto badpos;
        if (y > 0x3f)
            goto badpos;
        tile = MapA[x][y];
        if (TERRAINset == 0)
            ok = (tile <= 0x53);
        else
            ok = (tile <= 0x90);
        result = ok;
        return result;
    }

    if (x < 0)
        goto badpos;
    if (x > 0x3f)
        goto badpos;
    if (y < 0)
        goto badpos;
    if (y > 0x3f)
        goto badpos;

    if (plane == 2)
        tile = MapB[x][y];
    else
        tile = MapR[x][y];

    if (tile <= 0x18)
        goto pass_open;
    if (tile >= 0x30 && tile <= 0x31)
        goto pass_open;
    if (canDig == 0)
        goto fail_tile;
    if (tile >= 0x20 && tile <= 0x2e)
        goto pass_dig;
    if (tile >= 0x1c && tile <= 0x1f)
        goto pass_dig;

fail_tile:
    result = 0;
    goto haveResult;

pass_dig:
    result = 1;
    needsDig = 1;
    goto haveResult;

pass_open:
    result = 1;
    needsDig = 0;

haveResult:
    if (result == 0)
        goto fail;
    if (y > 1)
        goto fail;
    if (curPlane != plane)
        goto fail;

    if (canDig != 0 && needsDig != 0) {
        if (x != curX)
            return result;
        if (y != 0)
            goto fail;
        if (plane == 2)
            tile = MapB[x][y + 1];
        else
            tile = MapR[x][y + 1];
        if (tile >= 0x20 && tile <= 0x2e)
            goto fail;
        return result;
    }

    if (canDig != 0 && y != 0)
        return result;

    if (canDig == 0 && y != 0)
        goto fail;

    if (x != curX)
        goto fail;
    if (y == curY)
        return result;

fail:
    return 0;

badpos:
    return 0;
}
