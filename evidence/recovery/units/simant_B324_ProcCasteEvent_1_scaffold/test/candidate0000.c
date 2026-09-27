/* Candidate translation unit simant_B324_ProcCasteEvent_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ProcCasteEvent
 * SCAFFOLDED: unclaimed members _InitTriVars, _win_CasteControlChanged, _win_ModeControlChanged, _UpdateCasteWindow, _UpdateModeWindow are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct WinRect { int left; int top; int right; int bottom; };
struct Point { int x; int y; };
struct TriLevel { unsigned int frac; int unused2; unsigned int weight; };
struct ModeMsg {
    char pad0[8];
    int x;
    int y;
    int code;
};
extern int far CasteAuto;
extern int far casteVerts;
extern int near casteSet;
extern int near modeSet[];
extern int near win_hwnd[];
extern volatile unsigned int far casteLevels[];
extern int far IdealCaste[];
extern unsigned char far Dx8[];
#define HUNDRED 100UL
#define FIFTY 50UL
#define LDIV(a, b, c) ((long)(a) * (b) / (long)(c))
#define CUR_LEVEL (*(struct TriLevel far *)casteLevels)
#define MODE_DEFAULT(i) (*(struct TriLevel far *)&Dx8[(i) * 6 - 0x79c6])
extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void DoWinHelp(unsigned int context);
extern void far win_MakeGroupInvisible(int window, int group);
extern void far win_MakeGroupVisible(int window, int group);
extern void far win_SetGroupSelectedObj(int window, int group, int object);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far UpdateCasteWindow(void);
extern void far BoundPointToTri(struct Point far *pt, struct WinRect far *r);
extern void far GetTriLatDist(struct TriLevel far *level, struct WinRect far *rect,
                               struct Point far *pt);
extern void far GetMousePos(struct Point far *pt);
extern int far pascal ScreenToClient(int hwnd, struct Point far *pt);
extern int far StillDown(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far DrawControlLevels(int window, int index, int level);
extern int far memcmp(const void far *, const void far *, unsigned int);

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
extern int far modeButtonState;  /* scaffold reference for pool word C132 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CurRestPlane;  /* scaffold reference for pool word C134 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far StoreArray;  /* scaffold reference for pool word C136 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far mapCursorRect;  /* scaffold reference for pool word C138 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatCycle;  /* scaffold reference for pool word C13A (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_InitTriVars(void);
void far pool_stub_win_CasteControlChanged(void);
void far pool_stub_win_ModeControlChanged(void);
void far pool_stub_UpdateCasteWindow(void);
void far pool_stub_UpdateModeWindow(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitTriVars)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_CasteControlChanged)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_ModeControlChanged)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateCasteWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateModeWindow)

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
    t = modeButtonState;
    t = CurRestPlane;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateCasteWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C136 C138; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateCasteWindow(void)
{
    volatile int t;

    t = StoreArray;
    t = mapCursorRect;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateModeWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C13A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateModeWindow(void)
{
    volatile int t;

    t = CatCycle;
}

void far ProcCasteEvent(struct ModeMsg far *msg)
{
    struct WinRect rect;
    struct Point last;
    int left, right, bottom, top;
    int x, y, mid;
    int inside;
    long edge2, edge1;

    clip_SetWin(0x1300);

    switch (msg->code - 0x1303) {
    case 0:
        DoWinHelp(0x130e);
        break;

    case 1:
        if (CasteAuto == 0) {
            CasteAuto = 1;
            win_MakeGroupInvisible(0x1300, 4);
        }
        break;

    case 3:
    case 4:
    case 5:
        win_SetGroupSelectedObj(0x1300, 3, 0x1305);
        MODE_DEFAULT(casteSet) = CUR_LEVEL;
        casteSet = msg->code - 0x1306;
        CUR_LEVEL = MODE_DEFAULT(casteSet);
        UpdateCasteWindow();
        /* fall through */
    case 2:
        if (CasteAuto != 0) {
            CasteAuto = 0;
            win_MakeGroupVisible(0x1300, 4);
        }
        break;

    case 10:
        win_GetObjRect(0x130d, &rect);
        top = rect.top;
        bottom = rect.bottom;
        right = rect.right;
        left = rect.left;
        mid = (right + left) / 2;
        x = msg->x;
        y = msg->y;
        if (y >= bottom || y < top) {
            inside = 0;
        } else {
            edge1 = LDIV(left - mid, y - bottom, bottom - top) + left;
            if (edge1 > x) {
                inside = 0;
            } else {
                edge2 = LDIV(mid - right, y - top, top - bottom) + mid;
                if (edge2 < x)
                    inside = 0;
                else
                    inside = 1;
            }
        }
        if (inside) {
            if (CasteAuto != 0) {
                CasteAuto = 0;
                win_SetGroupSelectedObj(0x1300, 3, 0x1305);
                win_MakeGroupVisible(0x1300, 4);
            }
            last.x = 0xffff;
            clip_SetWin(0x1300);
            do {
                if (memcmp((const void far *)&last, (const void far *)&msg->x, 4) != 0) {
                    last = *(struct Point far *)&msg->x;
                    BoundPointToTri((struct Point far *)&msg->x, &rect);
                    GetTriLatDist(&CUR_LEVEL, (struct WinRect far *)&casteVerts,
                                  (struct Point far *)&msg->x);
                    UpdateCasteWindow();
                }
                GetMousePos((struct Point far *)&msg->x);
                ScreenToClient(win_hwnd[19], (struct Point far *)&msg->x);
            } while (StillDown());
            MODE_DEFAULT(casteSet) = CUR_LEVEL;
            IdealCaste[0] = (HUNDRED * casteLevels[1] + 0x3fff) / 0xffff;
            IdealCaste[1] = (HUNDRED * casteLevels[2] + 0x3fff) / 0xffff;
            IdealCaste[3] = IdealCaste[2] =
                (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
        }
        break;
    case 12:
    case 13:
    case 14:
        modeSet[10] ^= 1;
        MSClipStart(win_hwnd[19]);
        DrawControlLevels(0x1300, 0, modeSet[10]);
        MSClipEnd();
        break;

    default:
        break;
    }

    clip_Off();
}

