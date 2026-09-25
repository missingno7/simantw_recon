/*
 * Yard ribbon event dispatch, following the packet's cs jump table.
 * The message-0x2302 path checks/open window 0x1900 before switching to
 * the map with YardToMap.  The mode, queen prompt, placement, help, ribbon
 * button, bookmark, and point-hit paths mirror the observed calls and
 * argument fields in the remaining table cases.
 */
struct EditEvent {
    char reserved[8];
    int x;
    int y;
    int message;
};

extern int near YardMode;
extern int near MeType;
extern int far CurGameType;
extern long far * far WindPromptStrs;
extern int far FlyAwayB;
extern int far LayDownQueenMode;
extern int near win_hwnd[];
static int near yardDrawFlag = 1;
static int near yardPromptCountA;
static int near yardPromptCountB;

extern int far win_IsWinOpen(int window);
extern void far win_Open(int window);
extern void far YardToMap(void);
extern void far SetYardMode(int mode);
extern void far myBeginSound(unsigned int first,
                             unsigned int second,
                             unsigned int third);
extern void far EditMessage(long position, int a, int b, int mode);
extern void far PlaceQueenInYard(void);
extern void far win_MakeObjSelected(int object);
extern void far win_MakeObjUnselected(int object);
extern void far Draw_SimYard(int mode, int selector);
extern void far pascal UpdateWindow(int window);
extern void far DrawYardData(void);
extern void far DoWinHelp(int mode);
extern void far UpdateLayQueenModeDisplay(void);
extern void far DoUserButton(int message, int index);
extern void far DoBookMark(int index);
extern int far win_IsPointInObj(void far *point, int object);
extern void far DoHealthSetY(struct EditEvent far *event, int mode);
extern void far DoWarnSetB(struct EditEvent far *event, int mode);
extern void far DrawCastePopUp(void);

void far ProcYardRibbonEvent(struct EditEvent far *event)
{
    int dx;

    switch (event->message) {
    case 0x2302:
        if (!win_IsWinOpen(0x1900))
            win_Open(0x1900);
        YardToMap();
        break;
    case 0x2303:
        if (!win_IsWinOpen(0x1900))
            win_Open(0x1900);
        if (YardMode < 2)
            SetYardMode(YardMode ^ 1);
        else
            SetYardMode(0);
        break;
    case 0x2304:
        if (!win_IsWinOpen(0x1900))
            win_Open(0x1900);
        SetYardMode(2);
        break;
    case 0x2305:
        if (!win_IsWinOpen(0x1900))
            win_Open(0x1900);
        SetYardMode(3);
        break;
    case 0x2306:
        if (CurGameType != 2) {
            myBeginSound(0x7e, 0, 1);
            EditMessage(WindPromptStrs[15], 0xb4, 0, 1);
            return;
        }
        dx = yardPromptCountA + yardPromptCountB;
        if (MeType == 0x40 || MeType == 0x20)
            --dx;
        if (dx > 0) {
            FlyAwayB = 0xc8;
            myBeginSound(0x7e, 0, 1);
            EditMessage(WindPromptStrs[6], 0xb4, 0, 1);
        } else {
            myBeginSound(0x7e, 0, 1);
            EditMessage(WindPromptStrs[5], 0xb4, 0, 1);
        }
        return;
    case 0x2307:
        win_MakeObjSelected(0x230a);
        win_MakeObjSelected(0x2307);
        PlaceQueenInYard();
        if (win_IsWinOpen(0x1900)) {
            Draw_SimYard(YardMode, 1);
            yardDrawFlag = 0;
            UpdateWindow(win_hwnd[25]);
            yardDrawFlag = 1;
            DrawYardData();
        }
        win_MakeObjUnselected(0x2307);
        break;
    case 0x2308:
        DoWinHelp(0x2308);
        break;
    case 0x2309:
        LayDownQueenMode = 1;
        UpdateLayQueenModeDisplay();
        break;
    case 0x230a:
        LayDownQueenMode = 0;
        UpdateLayQueenModeDisplay();
        break;
    case 0x230b:
    case 0x230c:
    case 0x230d:
    case 0x230e:
    case 0x230f:
    case 0x2310:
    case 0x2311:
    case 0x2312:
        DoUserButton(event->message, event->message - 0x230b);
        break;
    case 0x2313:
    case 0x2314:
    case 0x2315:
    case 0x2316:
    case 0x2317:
    case 0x2318:
        DoBookMark(event->message - 0x2313);
        break;
    case 0x2324:
        if (win_IsPointInObj((char far *)event + 8, 0x231f))
            DoHealthSetY(event, 0x231f);
        else if (win_IsPointInObj((char far *)event + 8, 0x2320))
            DoWarnSetB(event, 0x2320);
        else
            DrawCastePopUp();
        return;
    }
}
