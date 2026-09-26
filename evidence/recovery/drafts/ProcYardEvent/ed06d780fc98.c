/* ProcYardEvent residue experiment 02_positive_else_first: isolate caller ABI and prompt branch scheduling. */
/*
 * ProcYardEvent: dense switch on event->message (same struct-EditEvent
 * shape as the admitted ProcEditEvent: a lone far struct pointer, only the
 * message word at offset 0xc read) for the yard/queen-placement edit
 * screen.  Messages 0x1902-0x1911 dispatch through a cs: jump table (16
 * slots after "sub ax,0x1902"; holes 0x1903-0x1906, 0x190c and 0x190f fall
 * to the shared no-op default).
 *   0x1902 - forward the event to YardArea(event).
 *   0x1907 - YardToMap().
 *   0x1908 - toggle SetYardMode between 0/1, forcing 0 once YardMode
 *       already reached 2 or more.
 *   0x1909 - SetYardMode(2).
 *   0x190a - SetYardMode(3).
 *   0x190b - queen-placement prompt.  Outside CurGameType 2 it plays the
 *       alert sound and shows WindPromptStrs[15], then returns.  In game
 *       type 2 it adds two private near counters (evidence: unnamed DS
 *       words at 0xac9a/0xac9c, read-only here), subtracts one when
 *       MeType is 0x40 or 0x20 (the two life stages that already left the
 *       nest), and shows WindPromptStrs[6] after marking FlyAwayB when the
 *       result is still positive, otherwise WindPromptStrs[5]; either way
 *       it returns immediately after the prompt.
 *   0x190d/0x190e - set/clear LayDownQueenMode and refresh its display,
 *       returning immediately (no common exit).
 *   0x1910 - select both queen-placement window objects, PlaceQueenInYard,
 *       and when window 0x1900 is open redraw the yard (toggling the
 *       private yardDrawFlag around the pascal UpdateWindow call) before
 *       deselecting the second object.
 *   0x1911 - DoWinHelp(0x1906).
 */
struct EditEvent {
    char reserved[12];
    int message;
};

extern int near YardMode;
extern int near MeType;
extern int far CurGameType;
extern long far *far WindPromptStrs;
extern int far FlyAwayB;
extern int far LayDownQueenMode;
extern int near win_hwnd[];
static int near yardDrawFlag = 1;
extern int near yardPromptCountA;  /* unnamed DS word at 0xac9a (44186) */
extern int near yardPromptCountB;  /* unnamed DS word at 0xac9c (44188) */

extern void near YardArea(struct EditEvent far *event);
extern void far YardToMap(void);
extern void far SetYardMode(int mode);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far EditMessage(long position, int a, int b, int mode);
extern void far UpdateLayQueenModeDisplay(void);
extern void far win_MakeObjSelected(int obj);
extern void far win_MakeObjUnselected(int obj);
extern void far PlaceQueenInYard(void);
extern int far win_IsWinOpen(int window);
extern void near Draw_SimYard(int mode, int selector);
extern void far pascal UpdateWindow(int window);
extern void near DrawYardData(void);
extern void far DoWinHelp(int mode);

void far ProcYardEvent(struct EditEvent far *event)
{
    int dx;

    switch (event->message) {
    case 0x1902:
        YardArea(event);
        break;
    case 0x1907:
        YardToMap();
        break;
    case 0x1908:
        if (YardMode < 2)
            SetYardMode(YardMode ^ 1);
        else
            SetYardMode(0);
        break;
    case 0x1909:
        SetYardMode(2);
        break;
    case 0x190a:
        SetYardMode(3);
        break;
    case 0x190b:
        if (CurGameType != 2) {
            myBeginSound(0x7e, 0, 1);
            EditMessage(WindPromptStrs[15], 0xb4, 0, 1);
            return;
        }
        dx = yardPromptCountA + yardPromptCountB;
        if (MeType == 0x40 || MeType == 0x20)
            dx--;
        if (dx <= 0) {
            myBeginSound(0x7e, 0, 1);
            EditMessage(WindPromptStrs[5], 0xb4, 0, 1);
        } else {
            FlyAwayB = 0xc8;
            myBeginSound(0x7e, 0, 1);
            EditMessage(WindPromptStrs[6], 0xb4, 0, 1);
        }
        return;
    case 0x190d:
        LayDownQueenMode = 1;
        UpdateLayQueenModeDisplay();
        return;
    case 0x190e:
        LayDownQueenMode = 0;
        UpdateLayQueenModeDisplay();
        return;
    case 0x1910:
        win_MakeObjSelected(0x190e);
        win_MakeObjSelected(0x1910);
        PlaceQueenInYard();
        if (win_IsWinOpen(0x1900)) {
            Draw_SimYard(YardMode, 1);
            yardDrawFlag = 0;
            UpdateWindow(win_hwnd[25]);
            yardDrawFlag = 1;
            DrawYardData();
        }
        win_MakeObjUnselected(0x1910);
        break;
    case 0x1911:
        DoWinHelp(0x1906);
        break;
    }
}
