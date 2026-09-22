/* Candidate translation unit antedit_00F4_UpdateEditWindow_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _UpdateEditWindow, _UpdateEditIfBufInvalid
 * SCAFFOLDED: unclaimed members _OverlayTileSet, _LoadTiles are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern void far UpdateEdit(void);
extern int far editBufInvalidFlag;
extern int near win_hwnd;
extern int near editForce;
extern int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern int far pascal GetUpdateRgn(int window, int region, int erase);
extern int far pascal ValidateRgn(int window, int region);
extern int far pascal UpdateWindow(int window);
extern int far pascal DeleteObject(int object);

extern int far Dx8;  /* scaffold reference for pool word BF7E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far TERRAINset;  /* scaffold reference for pool word BF80 (segment 9, MAPSYM_SITE_NAME) */
extern int far match_position;  /* scaffold reference for pool word BF82 (segment 9, MAPSYM_SITE_NAME) */
extern int far Barrier;  /* scaffold reference for pool word BF84 (segment 9, MAPSYM_SITE_NAME) */
extern int far match_length;  /* scaffold reference for pool word BF86 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word BF88 (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_OverlayTileSet(void);
void far pool_stub_LoadTiles(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_OverlayTileSet)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_LoadTiles)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _OverlayTileSet.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF7E BF80 BF82 BF84; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_OverlayTileSet(void)
{
    volatile int t;

    t = Dx8;
    t = TERRAINset;
    t = match_position;
    t = Barrier;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _LoadTiles.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF86 BF88 BF8A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_LoadTiles(void)
{
    volatile int t;

    t = match_length;
    t = pack_buf;
    t = (int)editBufInvalidFlag;
}

void UpdateEditWindow(void)
{
    UpdateEdit();
}

void far UpdateEditIfBufInvalid(void)
{
    int region;

    if (!editBufInvalidFlag)
        return;

    region = CreateRectRgn(0, 0, 10, 10);
    GetUpdateRgn(win_hwnd, region, 0);
    ValidateRgn(win_hwnd, region);
    UpdateWindow(win_hwnd);
    DeleteObject(region);
    editForce = 1;
    DrawEdit();
    editForce = 0;
}

