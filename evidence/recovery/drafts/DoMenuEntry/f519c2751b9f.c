/*
 * DoMenuEntry: ribbon/menu command dispatcher. If help mode is active
 * (bHelp != 0), clear it and route to ProcMenuHelp(entry); otherwise
 * decode the entry through ProcMenu(&action) (entry stored into the
 * action buffer at its bp-4 field) and, if a file-wait state is now
 * pending (fileWaitFlag != 0), dispatch on it: 4 = LoadGame (kills the
 * root window's timer, loads, centers the edit view on MeLocX/MeLocY,
 * redraws the map cursor if the yard window is closed, re-syncs the
 * pack tile-set slot and resets the seven bookmark records exactly as
 * the admitted ClearBookmarks loop does); 5 = abort via CleanUp; 6 =
 * discard (KillTimer only); 8 = SaveGame; anything else (7, etc.) just
 * falls through. Every path converges on re-arming the root window's
 * timer and clearing fileWaitFlag.
 */
struct MenuAction {
    int unused0, unused1, unused2, unused3, unused5, unused6, entry, unused7;
};

struct BookMark {
    int object;
    int plane;
    int x;
    int y;
    int flags;
};

extern int near bHelp;
extern int near fileWaitFlag;
extern int near rootWnd;
extern int near win_hwnd[];
extern int near MePlane;
extern int near YardMode;
extern int near MeLocX;
extern int near MeLocY;
extern unsigned long near lpTimerFunc;
extern struct BookMark far bookMark[7];
extern int far CurGameType;
extern int far editForce;
extern int near NewGame(int mode);
extern int near MenuQuit(void);

extern void far ProcMenuHelp(int entry);
extern void far ProcMenu(struct MenuAction far *action);
extern void far SetMapPlane(int plane);
extern void far SetYardMode(int mode);
extern int far LoadGame(int a, int b);
extern int far SaveGame(int a);
extern void far YardToMap(void);
extern int far CenterEdit(int x, int y);
extern int far win_IsWinOpen(int object);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far EraseMapCursor(void);
extern void far DrawMapCursor(void);
extern void far UpdateEdit(void);
extern void far CleanUp(void);
extern void far win_SetButtonBitmaps(int objectNumber, unsigned int bitmapUp,
                                     unsigned int bitmapDown);
extern void far win_SetObjSelectedState(int object, int selected);
extern void far pascal KillTimer(int window, int id);
extern unsigned int far pascal SetTimer(int window, int id, unsigned int elapse,
                                        unsigned long timerFunc);

void far DoMenuEntry(int entry)
{
    struct MenuAction action;
    int i;
    unsigned char saveMode;

    if (bHelp != 0) {
        bHelp = 0;
        ProcMenuHelp(entry);
        return;
    }

    action.entry = entry;
    ProcMenu(&action);

    if (fileWaitFlag != 0) {
        switch (fileWaitFlag) {
        case 4:
            KillTimer(rootWnd, 0);
            if (LoadGame(0, 0) != 0) {
                SetMapPlane(MePlane);
                if (MePlane == 0)
                    SetYardMode(YardMode);
                else if (!win_IsWinOpen(0x100))
                    YardToMap();
                if (CenterEdit(MeLocX, MeLocY) == 0) {
                    if (win_IsWinOpen(0x100)) {
                        MSClipStart(win_hwnd[1]);
                        EraseMapCursor();
                        DrawMapCursor();
                        MSClipEnd();
                    }
                    editForce = 1;
                    UpdateEdit();
                    for (i = 0; i < 7; i++) {
                        bookMark[i].object = -1;
                        bookMark[i].plane = 0;
                        bookMark[i].x = 0;
                        bookMark[i].y = 0;
                        bookMark[i].flags = 0;
                        win_SetButtonBitmaps(0x2218 + i, 0x3899 + i, 0x3867 + i);
                        win_SetObjSelectedState(0x2218 + i, 0);
                        win_SetButtonBitmaps(0x2313 + i, 0x3899 + i, 0x3867 + i);
                        win_SetObjSelectedState(0x2313 + i, 0);
                    }
            if (CurGameType == -1 && NewGame(0) < 0)
                goto cleanup;
                }
            }
            break;
        case 5:
            KillTimer(rootWnd, 0);
            saveMode = 1;
            goto save_call;
        case 6:
            KillTimer(rootWnd, 0);
            saveMode = 0;
        save_call:
            SaveGame(saveMode);
            break;
        case 8:
            KillTimer(rootWnd, 0);
            if (MenuQuit() != 0)
                goto cleanup;
            break;
        default: break;
    }
goto after_cleanup;
cleanup:
    CleanUp();
    goto menu_done;
after_cleanup: ;
    }

    SetTimer(rootWnd, 0, 0x11, lpTimerFunc);
menu_done:
    fileWaitFlag = 0;
}
