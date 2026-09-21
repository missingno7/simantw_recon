/*
 * ProcModeEvent: dense switch (msg->code - 0x1203, 15 cases) dispatching the
 * mode-tool window's control events (object 0x1200 family).  0x1203 shows
 * mode help (0x120e).  0x1204 hides group 4 once, guarded by the shared
 * near ModeAuto flag.  0x1206/0x1207/0x1208 select control 3 (object
 * 0x1205), latch modeSet to the pressed control and save the currently
 * edited level (segment9 record at match_position word index 0x4e3a) into
 * the matching Dx8 default-level slot (six bytes at Dx8[modeSet*6-0x79a8]),
 * refresh the window, and fall into 0x1205's body, which un-selects and
 * shows group 4 while ModeAuto is set.  0x120d is a mouse-down inside the
 * iso-triangle diagram (win_GetObjRect(0x120d)): while the button stays
 * down (StillDown), the clamped point (BoundPointToTri) is fed to
 * GetTriLatDist to update the live level record and the window, tracking
 * screen position through GetMousePos/ScreenToClient; on release the live
 * level is re-saved into Dx8's slot for the current modeSet.  0x120f/
 * 0x1210/0x1211 toggle the private near modeDrag byte/word and redraw the
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

extern int far ModeAuto;
extern int near modeSet;
static int near modeDrag;
extern int near win_hwnd[];
extern int far match_position[];
extern unsigned char far Dx8[];

#define LDIV(a, b, c) ((long)(a) * (b) / (long)(c))
#define CUR_LEVEL (*(struct TriLevel far *)&match_position[0x4e3a])
#define MODE_DEFAULT(i) (*(struct TriLevel far *)&Dx8[(i) * 6 - 0x79a8])

extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void DoWinHelp(unsigned int context);
extern void far win_MakeGroupInvisible(int window, int group);
extern void far win_MakeGroupVisible(int window, int group);
extern void far win_SetGroupSelectedObj(int window, int group, int object);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far UpdateModeWindow(void);
extern void far BoundPointToTri(struct Point far *pt, struct WinRect far *r);
extern void far GetTriLatDist(struct TriLevel far *level, struct WinRect far *rect,
                               struct Point far *pt);
extern void far GetMousePos(struct Point far *pt);
extern int far pascal ScreenToClient(int hwnd, struct Point far *pt);
extern int far StillDown(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far DrawControlLevels(int window, int index, int level);

void far ProcModeEvent(struct ModeMsg far *msg)
{
    struct WinRect rect;
    struct Point far *pt;
    struct Point last;
    int mid, x, y, inside;
    long edge1, edge2;

    clip_SetWin(0x1200);

    switch (msg->code - 0x1203) {
    case 0:
        DoWinHelp(0x120e);
        break;

    case 1:
        if (ModeAuto == 0) {
            ModeAuto = 1;
            win_MakeGroupInvisible(0x1200, 4);
        }
        break;

    case 3:
    case 4:
    case 5:
        win_SetGroupSelectedObj(0x1200, 3, 0x1205);
        MODE_DEFAULT(modeSet) = CUR_LEVEL;
        modeSet = msg->code - 0x1206;
        CUR_LEVEL = MODE_DEFAULT(modeSet);
        UpdateModeWindow();
        /* fall through */
    case 2:
        if (ModeAuto != 0) {
            ModeAuto = 0;
            win_SetGroupSelectedObj(0x1200, 3, 0x1205);
            win_MakeGroupVisible(0x1200, 4);
        }
        break;

    case 10:
        win_GetObjRect(0x120d, &rect);
        mid = (rect.right + rect.left) / 2;
        x = msg->x;
        y = msg->y;
        inside = 0;
        if (y < rect.bottom && y >= rect.top) {
            edge1 = LDIV(rect.left - mid, y - rect.bottom, rect.bottom - rect.top) + rect.left;
            if (x >= edge1) {
                edge2 = LDIV(mid - rect.right, y - rect.top, rect.top - rect.bottom) + mid;
                if (x <= edge2)
                    inside = 1;
            }
        }
        if (inside) {
            if (ModeAuto != 0) {
                ModeAuto = 0;
                win_SetGroupSelectedObj(0x1200, 3, 0x1205);
                win_MakeGroupVisible(0x1200, 4);
            }
            last.x = 0xffff;
            clip_SetWin(0x1200);
            pt = (struct Point far *)&msg->x;
            do {
                if (last.x != pt->x || last.y != pt->y) {
                    last = *pt;
                    BoundPointToTri(pt, &rect);
                    GetTriLatDist(&CUR_LEVEL, &rect, pt);
                    UpdateModeWindow();
                }
                GetMousePos(pt);
                ScreenToClient(win_hwnd[18], pt);
            } while (StillDown());
            MODE_DEFAULT(modeSet) = CUR_LEVEL;
        }
        break;

    case 12:
    case 13:
    case 14:
        modeDrag ^= 1;
        MSClipStart(win_hwnd[18]);
        DrawControlLevels(0x1200, 0, modeDrag);
        MSClipEnd();
        break;

    default:
        break;
    }

    clip_Off();
}
