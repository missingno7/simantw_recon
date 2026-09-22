/* DoScenario: open the scenario-select window (object 0x200), capture the
 * mouse on win_hwnd[2] and run its modal event loop.  Each turn:
 * win_GetEvent fills a 16-byte event buffer whose word at +0xc is the
 * event's owning object; when there is no event, or it belongs to our own
 * window (0x200), DialogClearWait marks the wait, then either DialogAbort
 * or an Enter keypress (GetAsyncKeyState(0xd) & 0x8000) ends the dialog:
 * re-affirm the mouse capture if it is still on a visible window, else
 * release it, close the window, finish the dialog wait and return a
 * distinct status (0x205 for abort, 0x203 for Enter) -- otherwise loop.
 * An event belonging to a different window ends the dialog too: tag the
 * still-visible captured window with the private GetProp marker and
 * re-affirm capture, or release it; close the window, refresh every
 * window and return the event's object.
 */

struct DialogEvent {
    unsigned char unused1[12];
    int object;               /* +0xc */
    unsigned char unused2[2];
};

static char near scenarioPropName[] = "INDEX";

extern int near win_hwnd[];

extern void far win_Open(int window);
extern void far win_Close(int objectNumber);
extern void far win_FlushEvents(void);
extern int far win_GetEvent(struct DialogEvent far *event);
extern void far UpdateAllWindows(void);

extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);

extern void far DialogClearWaitInit(void);
extern void far DialogClearWait(void);
extern int far DialogAbort(void);
extern void far DialogDone(void);

extern int far pascal IsWindowVisible(unsigned int window);
extern int far pascal GetAsyncKeyState(unsigned int key);
extern unsigned int far pascal GetProp(unsigned int window, char far *string);

int far DoScenario(void)
{
    struct DialogEvent event;
    int captured;

    win_Open(0x200);
    captured = MySetCapture(win_hwnd[2]);
    win_FlushEvents();
    DialogClearWaitInit();

    for (;;) {
        if (!win_GetEvent(&event) || event.object == 0x200) {
            DialogClearWait();
            if (DialogAbort()) {
                if (captured && IsWindowVisible(captured))
                    MySetCapture(captured);
                else
                    MyReleaseCapture();
                win_Close(0x200);
                DialogDone();
                return 0x205;
            }
            if (GetAsyncKeyState(0xd) & 0x8000) {
                if (captured && IsWindowVisible(captured))
                    MySetCapture(captured);
                else
                    MyReleaseCapture();
                win_Close(0x200);
                DialogDone();
                return 0x203;
            }
        } else {
            DialogDone();
            if (captured && IsWindowVisible(captured)) {
                GetProp(captured, scenarioPropName);
                MySetCapture(captured);
            } else {
                MyReleaseCapture();
            }
            win_Close(0x200);
            UpdateAllWindows();
            return event.object;
        }
    }
}
