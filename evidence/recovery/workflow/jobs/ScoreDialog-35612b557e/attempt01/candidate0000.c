/* ScoreDialog: compute the overall score into the far OverallScore long,
 * refresh the four team-score fields (objects 0x1802..0x1805) from the
 * scores CalcScore fills in, and the score dialog's title text (object
 * 0x180c) from WindPromptStrs' far string field, then lock, open and run
 * the modal score dialog window (object 0x1800): poll DialogClearWait /
 * win_Events / DialogAbort each turn, releasing the mouse capture and
 * closing the window as soon as either an event or an abort fires, until
 * the window itself is no longer open; finally DialogDone, flush events
 * and unlock the window.
 */

extern void far CalcScore(int far *scores);
extern long far OverallScore;

struct WindPromptTable {
    int header[4];
    long yardPrompt;             /* +8  */
    long toolTenPrompt;          /* +0xc */
    int filler1[20];             /* +0x10 .. +0x37 */
    char far *scoreTitlePrompt;  /* +0x38 */
    int filler2[4];              /* +0x3c .. +0x43 */
    long toolElevenPrompt;       /* +0x44 */
};
extern struct WindPromptTable far * far WindPromptStrs;

extern int near win_hwnd[];

extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far win_SetObjFormatStr();
extern void far win_FlushEvents(void);
extern void far win_Open(int window);
extern int far win_IsWinOpen(int window);
extern void far win_Close(int objectNumber);
extern int far win_Events(void);

extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);

extern void far font_SetFont(int font);

extern void far DialogClearWaitInit(void);
extern void far DialogClearWait(void);
extern int far DialogAbort(void);
extern void far DialogDone(void);

void far ScoreDialog(void)
{
    int scores[4];
    int i;
    int unused;

    OverallScore = CalcScore(scores);

    win_LockWin(0x1800);

    for (i = 0; i < 4; i++)
        win_SetObjFormatStr(0x1802 + i, scores[i]);
    win_SetObjFormatStr(0x180c, WindPromptStrs->scoreTitlePrompt);

    win_FlushEvents();
    win_Open(0x1800);
    MySetCapture(win_hwnd[24]);

    unused = 0;
    font_SetFont(0);

    DialogClearWaitInit();
    if (win_IsWinOpen(0x1800)) {
        do {
            DialogClearWait();
            if (win_Events() || DialogAbort()) {
                MyReleaseCapture();
                win_Close(0x1800);
            }
        } while (win_IsWinOpen(0x1800));
    }

    DialogDone();
    win_FlushEvents();
    win_UnlockWin(0x1800);
}
