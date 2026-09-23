/*
 * ProcMapRibbonEvent dispatches ribbon command messages 0x2202..0x2227.
 * MAPMODE uses the named far global and its selector-backed ES accesses;
 * event->message is at 0x0c and event->value at 0x08. The two unnamed
 * near words at DGROUP offsets BCA8/BCD8 are hypothesized ribbon/map
 * window handles; this isolated draft leaves them as a pending private
 * data question for strict matching.
 */
struct EditEvent {
    char reserved[8];
    int value;
    char reserved2[2];
    int message;
};
struct WinRect { int left, top, right, bottom; };
extern int far MapMode;
extern int far LessonTemp;
extern int near ELayerMode;
extern int far win_IsWinOpen(int window);
extern void far win_Open(int window);
extern int far pascal BringWindowToTop(int window);
extern void far MapToYard(void);
extern void far ClearMapScentButtons(void);
extern void far SetMapPlane(int plane);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far OpenMiniMapWin(int x, int y);
extern void far GotoSpider(void);
extern void far DoWinHelp(int mode);
extern void far ScoreDialog(void);
extern void far RibbonToolsMenu(void);
extern void far SetMapModeAnt(int mode);
extern void near MapModeMismatch(void);
extern void far DoUserButton(int message, int index);
extern void far DoBookMark(int index);
extern int far win_IsPointInObj(void far *point, int object);
extern void far DoHealthSetY(struct EditEvent far *event, int mode);
extern void far DoWarnSetB(struct EditEvent far *event, int mode);
extern void far DrawCastePopUp(void);

static int near ribbonWindow;
static int near mapWindow;

void far ProcMapRibbonEvent(struct EditEvent far *event)
{
    struct WinRect second, first;
    int x;

    switch (event->message) {
    case 0x2202:
        if (!win_IsWinOpen(0x100) && !win_IsWinOpen(0x1900))
            win_Open(0x100);
        if (win_IsWinOpen(0x1900))
            BringWindowToTop(ribbonWindow);
        else {
            BringWindowToTop(mapWindow);
            MapToYard();
        }
        break;
    case 0x2203:
        ClearMapScentButtons(); SetMapPlane(2); break;
    case 0x2204:
        ClearMapScentButtons(); SetMapPlane(3); break;
    case 0x2205:
        ClearMapScentButtons(); SetMapPlane(1); break;
    case 0x2206:
        win_GetObjRect(event->message, &first);
        win_GetObjRect(0x1400, &second);
        x = first.left + (first.right - first.left) >> 1
            - (second.right - second.left) >> 1;
        OpenMiniMapWin(x, 0);
        break;
    case 0x2207:
        GotoSpider();
        return;
    case 0x2208:
        LessonTemp = 1;
        DoWinHelp(0x2208);
        break;
    case 0x2209:
        ScoreDialog();
        return;
    case 0x220a:
        RibbonToolsMenu();
        return;
    case 0x220b:
        SetMapModeAnt(4);
        ELayerMode = (MapMode == 4) ? 1 : -1;
        MapModeMismatch();
        break;
    case 0x220c:
        SetMapModeAnt(5);
        ELayerMode = (MapMode == 5) ? 2 : -1;
        MapModeMismatch();
        break;
    case 0x220d:
        SetMapModeAnt(8);
        ELayerMode = (MapMode == 8) ? 0 : -1;
        MapModeMismatch();
        break;
    case 0x220e:
        SetMapModeAnt(6);
        ELayerMode = (MapMode == 6) ? 3 : -1;
        MapModeMismatch();
        break;
    case 0x220f:
        SetMapModeAnt(7);
        ELayerMode = (MapMode == 7) ? 4 : -1;
        MapModeMismatch();
        break;
    case 0x2210:
    case 0x2211:
    case 0x2212:
    case 0x2213:
    case 0x2214:
    case 0x2215:
    case 0x2216:
    case 0x2217:
        DoUserButton(event->message, event->message - 0x2210);
        break;
    case 0x2218:
    case 0x2219:
    case 0x221a:
    case 0x221b:
    case 0x221c:
    case 0x221d:
    case 0x221e:
        DoBookMark(event->message - 0x2218);
        break;
    case 0x2227:
        if (win_IsPointInObj((char far *)event + 8, 0x2222))
            DoHealthSetY(event, 0x231f);
        else if (win_IsPointInObj((char far *)event + 8, 0x2223))
            DoWarnSetB(event, 0x2320);
        else
            DrawCastePopUp();
        return;
    }
}





