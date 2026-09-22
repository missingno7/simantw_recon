/* EndGameDialog: play the win/lose tune (BlackWon selects which), post
 * the fixed defeat/victory message (EditMessage(0L,-2,-1,1)), open the
 * end-game window (object 0x400) and capture the mouse on win_hwnd[4],
 * make object 0x401 (the dismiss button) selectable, then run a modal
 * loop while the window stays open and it hasn't been dismissed: watch
 * for a win_GetEvent hit on object 0x401 (sets clicked) and, once the
 * current song finishes, queue one random ambient tune
 * (SRand2()+0x2713) exactly once.  On exit, re-affirm the mouse capture
 * (tagging the window with the private "INDEX" property) if it is still
 * on a visible window, else release it; close the window and refresh
 * every window.  Finally clear the dialog-wait ledger and start a new
 * game; if NewGame declines (negative result), clean up and post the
 * quit message.  OptionStates[1] gates the tune (index 1, same DGROUP
 * object PictStrnDialog indexes as OptionStates[3]).
 */

struct DialogEvent {
    unsigned char unused1[12];
    int object;               /* +0xc */
    unsigned char unused2[2];
};

extern int far OptionStates[];
extern int far BlackWon;
extern int near win_hwnd[];

extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void far EditMessage(long position, int a, int b, int mode);
extern void far win_Open(int window);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern void far UpdateAllWindows(void);
extern void far win_MakeObjSelectable(int objectNumber);
extern int far win_IsWinOpen(int window);
extern int far win_GetEvent(struct DialogEvent far *event);
extern int far mySongIsDone(void);
extern int far SRand2(void);
extern int far pascal IsWindowVisible(unsigned int window);
extern unsigned int far pascal GetProp(unsigned int window, char far *string);
extern void far win_Close(int objectNumber);

extern void far DialogAbortAll(void);
extern int far NewGame(int mode);
extern void far CleanUp(void);
extern void far pascal PostQuitMessage(int exitCode);

void far EndGameDialog(void)
{
    struct DialogEvent event;
    int captured;
    int songQueued;
    int clicked;

    if (OptionStates[1] != 0) {
        if (BlackWon == 0)
            myBeginSong(0x271a, 0x7e);
        else
            myBeginSong(0x2718, 0x7e);
    }

    EditMessage(0L, -2, -1, 1);

    win_Open(0x400);
    captured = MySetCapture(win_hwnd[4]);
    songQueued = 0;

    UpdateAllWindows();
    win_MakeObjSelectable(0x401);

    clicked = 0;
    while (win_IsWinOpen(0x400)) {
        if (clicked)
            break;

        if (win_GetEvent(&event) && event.object == 0x401)
            clicked = 1;

        if (mySongIsDone() && !songQueued) {
            songQueued = 1;
            myBeginSong(SRand2() + 0x2713, 0x7e);
        }
    }

    if (captured != 0 && IsWindowVisible(captured)) {
        GetProp(captured, "INDEX");
        MySetCapture(captured);
    } else {
        MyReleaseCapture();
    }
    win_Close(0x400);
    UpdateAllWindows();

    DialogAbortAll();
    if (NewGame(0) < 0) {
        CleanUp();
        PostQuitMessage(0);
    }
}
