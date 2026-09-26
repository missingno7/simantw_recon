/* Transfer a patch from the current yard point to a valid map cell. */
struct YardPoint { int x; int y; };
struct WindPromptTable {
    int header[4];
    long yardPrompt;
    long toolTenPrompt;
    int beforeOutside[12];
    long outsidePrompt;              /* target reads +0x28 */
    int betweenPrompts[6];
    char far *scoreTitlePrompt;
    int afterScoreTitle[4];
    long toolElevenPrompt;
    long reserved48;
    long occupiedPrompt;              /* target reads +0x4c */
    long transferPrompt;              /* target reads +0x50 */
};
struct XferEvent { unsigned char pad[8]; int y; int x; unsigned char pad2[4]; };
extern struct YardPoint far CurYardPnt;
extern unsigned char far YMapPopB[12][16];
extern int far ColonyUpdateFlag;
extern int near win_hwnd[];
extern struct WindPromptTable far * far WindPromptStrs;
extern int far patchRgn[];
extern int far mapTileRect[];
extern int far YMapPnt[2];
extern void far MapToYard(void);
extern int far win_IsWinInFront(int window);
extern int far win_IsWinOpen(int window);
extern void far win_ToTop(int window);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern void far SetYardMode(int mode);
extern void far SetMapPlane(int plane);
extern void far EditMessage(long position, int a, int b, int mode);
extern int far win_GetEvent(struct XferEvent far *event);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void near XferPatch(void);

struct XferState { struct XferEvent event; struct WindPromptTable far * far * promptTable; int completed; };
void far SpecialXfer(void)
{
    struct XferState state;
    register int x;
    register int y;

    YMapPopB[CurYardPnt.x][CurYardPnt.y] = 0;
    if (!win_IsWinInFront(0x1900)) {
        if (!win_IsWinOpen(0x1900))
            MapToYard();
        win_ToTop(0x1900);
    }
    MySetCapture(win_hwnd[1]);
    SetYardMode(2);
    ColonyUpdateFlag = 1;
    SetMapPlane(0);
    state.promptTable = &WindPromptStrs;
    EditMessage((*state.promptTable)->transferPrompt, -2, -1, 1);
    state.completed = 0;
    while (win_GetEvent(&state.event)) {
        if (!win_IsWinInFront(0x1900)) {
            if (!win_IsWinOpen(0x1900))
                MapToYard();
            win_ToTop(0x1900);
        }
        x = (state.event.x - patchRgn[1] - mapTileRect[1]) / 10;
        y = (state.event.y - patchRgn[0] - mapTileRect[0]) / 28;
        if (x < 0 || x > 15 || y < 0 || y > 11) {
            myBeginSound(1, 0, 0x7e);
            EditMessage((*state.promptTable)->outsidePrompt, 0x78, 0, 1);
        } else if (YMapPopB[y][x] != 0) {
            myBeginSong(0x2afb, 0x7e);
            YMapPnt[0] = y;
            YMapPnt[1] = x;
            XferPatch();
            state.completed = 1;
        } else {
            myBeginSound(1, 0, 0x7e);
            EditMessage((*state.promptTable)->occupiedPrompt, 0x78, 0, 1);
        }

        if (state.completed)
            break;
    }
    if (!state.completed) {
        MyReleaseCapture();
        EditMessage(0L, -2, -1, 1);
    }
}

