/*
 * ProcCasteEvent: dense switch (msg->code - 0x1303, 15 cases) dispatching the
 * caste-tool window's control events (object 0x1300 family) -- the B/R
 * twin of ProcModeEvent (object 0x1200 family), sharing simant:B324's
 * clip_SetWin/win_* helpers, BoundPointToTri/GetTriLatDist triangle math
 * and dense jump-table shape.  0x1303 shows caste help (0x130e).  0x1304
 * hides group 4 once, guarded by the named far CasteAuto flag (its own
 * public symbol, unlike ModeAuto it lives in the Dx8 selector but is still
 * independently named).  0x1306/0x1307/0x1308 select control 3 (object
 * 0x1305), latch casteSet to the pressed control and save the currently
 * edited level (the named far casteLevels record, admitted verbatim from
 * cvtLevels2IdealCaste) into the matching Dx8 default-level slot (six
 * bytes at Dx8[casteSet*6-0x79c6]), refresh the window, and fall into
 * 0x1305's body, which un-selects and shows group 4 while CasteAuto is
 * set.  0x130d is a mouse-down inside the iso-triangle diagram
 * (win_GetObjRect(0x130d)): while the button stays down (StillDown), the
 * clamped point (BoundPointToTri) is fed to GetTriLatDist to update the
 * live level record and the window, tracking screen position through
 * GetMousePos/ScreenToClient(win_hwnd[19]); on release the live level is
 * re-saved into Dx8's slot for the current casteSet, and the caste
 * percentages are recomputed inline (the same 100/100/50/50 rounded
 * unsigned-long-divide-by-0xffff shape as the admitted
 * cvtLevels2IdealCaste, but written out directly into IdealCaste[0..3]
 * rather than called through its far pointer parameter).  0x130f/0x1310/
 * 0x1311 toggle the private near casteDrag byte/word and redraw the
 * control levels bar while clip-guarding MSClipStart/End.  Every path
 * falls into the shared clip_Off() cleanup.
 */
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
extern int near casteSet;
static int near casteDrag;
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

void far ProcCasteEvent(struct ModeMsg far *msg)
{
    struct WinRect rect;
    struct Point last;
    int left, right, bottom, top;
    int x, y, mid;
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
            win_SetGroupSelectedObj(0x1300, 3, 0x1305);
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
        if (y < bottom && y >= top) {
            edge1 = LDIV(left - mid, y - bottom, bottom - top) + left;
            if (x >= edge1) {
                edge2 = LDIV(mid - right, y - top, top - bottom) + mid;
                if (x <= edge2) {
            if (CasteAuto != 0) {
                CasteAuto = 0;
                win_SetGroupSelectedObj(0x1300, 3, 0x1305);
                win_MakeGroupVisible(0x1300, 4);
            }
            last.x = 0xffff;
            clip_SetWin(0x1300);
            do {
                if (last.x != msg->x || last.y != msg->y) {
                    last.x = msg->x;
                    last.y = msg->y;
                    BoundPointToTri((struct Point far *)&msg->x, &rect);
                    GetTriLatDist(&CUR_LEVEL, &rect, (struct Point far *)&msg->x);
                    UpdateCasteWindow();
                }
                GetMousePos((struct Point far *)&msg->x);
                ScreenToClient(win_hwnd[19], (struct Point far *)&msg->x);
            } while (StillDown());
            MODE_DEFAULT(casteSet) = CUR_LEVEL;
            IdealCaste[0] = (HUNDRED * casteLevels[1] + 0x3fff) / 0xffff;
            IdealCaste[1] = (HUNDRED * casteLevels[2] + 0x3fff) / 0xffff;
            IdealCaste[2] = (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
            IdealCaste[3] = (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
                }
            }
        }
        break;

    case 12:
    case 13:
    case 14:
        casteDrag ^= 1;
        MSClipStart(win_hwnd[19]);
        DrawControlLevels(0x1300, 0, casteDrag);
        MSClipEnd();
        break;

    default:
        break;
    }

    clip_Off();
}
