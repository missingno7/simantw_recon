/* Candidate translation unit simant_B324_initControls_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _initControls
 * SCAFFOLDED: unclaimed members _InitTriVars, _win_CasteControlChanged, _win_ModeControlChanged, _UpdateCasteWindow, _UpdateModeWindow, _ProcCasteEvent, _ProcModeEvent are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct WinRect { int left; int top; int right; int bottom; };
struct BitmapSize { int width; int height; };
extern struct BitmapSize far knobSize;
extern int far ModeAuto;
extern int far CasteAuto;
extern int far ShowPercentMode;
extern int far ShowPercentCaste;
extern int far modeButtonState;
extern int far casteButtonState;
extern int far modeLevels[3];
extern int far modeLevelDefaults[3];
extern int far modeSetLevels[][3];
extern unsigned int far casteLevels[];
extern int far casteLevelDefaults[3];
extern int far casteSetLevels[][3];
extern int far IdealCaste[];
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far win_ModeControlChanged(void);
extern void far win_CasteControlChanged(void);
#define HUNDRED 100UL
#define FIFTY 50UL

extern int far match_position;  /* scaffold reference for pool word C11C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C11E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C120 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far triHeight;  /* scaffold reference for pool word C122 (segment 9, MAPSYM_SITE_NAME) */
extern int far Scycle;  /* scaffold reference for pool word C124 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C126 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C12A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C12C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C12E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SMode;  /* scaffold reference for pool word C130 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CurRestPlane;  /* scaffold reference for pool word C132 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far StoreArray;  /* scaffold reference for pool word C134 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far mapCursorRect;  /* scaffold reference for pool word C136 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatCycle;  /* scaffold reference for pool word C138 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far custNameStrHandle;  /* scaffold reference for pool word C13A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C13E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word C144 (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_InitTriVars(void);
void far pool_stub_win_CasteControlChanged(void);
void far pool_stub_win_ModeControlChanged(void);
void far pool_stub_UpdateCasteWindow(void);
void far pool_stub_UpdateModeWindow(void);
void far pool_stub_ProcCasteEvent(void);
void far pool_stub_ProcModeEvent(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitTriVars)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_CasteControlChanged)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_ModeControlChanged)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateCasteWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateModeWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcCasteEvent)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcModeEvent)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitTriVars.
 * It only reproduces the object's selector-pool allocation order for the
 * words C11C C11E C120 C122 C124; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitTriVars(void)
{
    volatile int t;

    t = match_position;
    t = match_length;
    t = pack_buf;
    t = triHeight;
    t = Scycle;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_CasteControlChanged.
 * It only reproduces the object's selector-pool allocation order for the
 * words C126 C128 C12A C12C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_CasteControlChanged(void)
{
    volatile int t;

    t = EditColumns;
    t = casteLevels[0];
    t = MiscStrs;
    t = LastQueenPlane;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_ModeControlChanged.
 * It only reproduces the object's selector-pool allocation order for the
 * words C12E C130 C132 C134; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_ModeControlChanged(void)
{
    volatile int t;

    t = EditDragPnt;
    t = SMode;
    t = CurRestPlane;
    t = StoreArray;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateCasteWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C136 C138; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateCasteWindow(void)
{
    volatile int t;

    t = mapCursorRect;
    t = CatCycle;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateModeWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C13A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateModeWindow(void)
{
    volatile int t;

    t = custNameStrHandle;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcCasteEvent.
 * It only reproduces the object's selector-pool allocation order for the
 * words C13C C13E C140; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ProcCasteEvent(void)
{
    volatile int t;

    t = (int)CasteAuto;
    t = Dx8;
    t = IdealCaste[0];
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcModeEvent.
 * It only reproduces the object's selector-pool allocation order for the
 * words C142 C144; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ProcModeEvent(void)
{
    volatile int t;

    t = (int)ModeAuto;
    t = Dy8;
}

void far initControls(void)
{
    struct WinRect rect;
    int i;

    gr_BitMapSize(&knobSize, 0x578);
    win_GetObjRect(0x120d, &rect);

    ModeAuto = 1;
    CasteAuto = 1;
    ShowPercentMode = 1;
    ShowPercentCaste = 1;
    modeButtonState = 0xffff;
    casteButtonState = 0xffff;

    for (i = 0; i < 3; i++) {
        modeLevels[i] = modeLevelDefaults[i];
        modeSetLevels[0][i] = modeLevelDefaults[i];
        casteLevels[i] = casteLevelDefaults[i];
        casteSetLevels[0][i] = casteLevelDefaults[i];
    }

    win_ModeControlChanged();
    win_CasteControlChanged();

    IdealCaste[0] = (HUNDRED * casteLevels[1] + 0x3fff) / 0xffff;
    IdealCaste[1] = (HUNDRED * casteLevels[2] + 0x3fff) / 0xffff;
    IdealCaste[2] = (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
    IdealCaste[3] = (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
}

