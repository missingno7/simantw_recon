/* Candidate translation unit simant_5530_DoWinHelp_4_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoWinHelp, _SetDefaultWindPrompt, _PictStrnDialog, _win_DrawPictureWindow
 * SCAFFOLDED: unclaimed members _CalcScore, _win_DrawScoreWindow, _ScoreDialog, _DrawCastePopUp are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int near rootWnd;
extern char far helpFile[];
extern int far pascal WinHelp(int window, char far *file,
                              unsigned int command, unsigned long data);
struct WindPromptTable {
    int header[4];
    long yardPrompt;        /* +8  */
    long toolTenPrompt;     /* +0xc */
    int filler[26];
    long toolElevenPrompt;  /* +0x44 */
};
extern int far GamePaused;
extern int far CurGameTool;
extern struct WindPromptTable far * far WindPromptStrs;
extern void far EditMessage(long position, int a, int b, int mode);
extern int far OptionStates[];
extern void far StopSimulation(void);
extern char far * far * far LoadStringAnt(int object);
extern void far PictureDialog(char far * far *strings, int count, int picture, int force);
extern void far free(void far *block);
extern void far db_PurgeObject(int object, int kind);
extern void far RestartSimulation(void);
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
struct BitmapSize {
    int width;
    int height;
};
static char far * far *pictureLines;
static int near pictureLineCount;
static unsigned int near pictureBitmap;
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);
extern void far font_SetFont(int font);
extern int far font_FontHeight(void);
extern void far win_SetColorFromObjNum(int objectNumber);
extern void far gr_CenterStrInRect(struct WinRect far *rect, char far *string);

extern int far HistStart;  /* scaffold reference for pool word BEDA (segment 9, MAPSYM_SITE_NAME) */
extern int far HistCnt;  /* scaffold reference for pool word BEDC (segment 8, MAPSYM_SITE_NAME) */
extern int far TotalEggsLaidB;  /* scaffold reference for pool word BEDE (segment 9, MAPSYM_SITE_NAME) */
extern int far TotalEggsDiedB;  /* scaffold reference for pool word BEE0 (segment 9, MAPSYM_SITE_NAME) */
extern int far BlackLost;  /* scaffold reference for pool word BEE2 (segment 9, MAPSYM_SITE_NAME) */
extern int far RedLost;  /* scaffold reference for pool word BEE4 (segment 9, MAPSYM_SITE_NAME) */
extern int far CurGameType;  /* scaffold reference for pool word BEE6 (segment 9, MAPSYM_SITE_NAME) */
extern int far BColoniesStarted;  /* scaffold reference for pool word BEE8 (segment 9, MAPSYM_SITE_NAME) */
extern int far RColoniesStarted;  /* scaffold reference for pool word BEEA (segment 9, MAPSYM_SITE_NAME) */
extern int far BColoniesKilled;  /* scaffold reference for pool word BEEC (segment 9, MAPSYM_SITE_NAME) */
extern int far OverallScore;  /* scaffold reference for pool word BEEE (segment 9, MAPSYM_SITE_NAME) */
extern int far MiscStrs;  /* scaffold reference for pool word BEF0 (segment 9, MAPSYM_SITE_NAME) */
extern int far ScenarioNameStrs;  /* scaffold reference for pool word BEF2 (segment 9, MAPSYM_SITE_NAME) */
extern int far LessonTemp;  /* scaffold reference for pool word BEF8 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_CalcScore(void);
void far pool_stub_win_DrawScoreWindow(void);
void far pool_stub_ScoreDialog(void);
void far pool_stub_DrawCastePopUp(void);
void far SetDefaultWindPrompt(int mode);
void far PictStrnDialog(int picture, int object, int force);
void far win_DrawPictureWindow(int flags);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_CalcScore)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_DrawScoreWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ScoreDialog)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawCastePopUp)
#pragma alloc_text(RUN2_TEXT, SetDefaultWindPrompt, PictStrnDialog, win_DrawPictureWindow)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _CalcScore.
 * It only reproduces the object's selector-pool allocation order for the
 * words BEDA BEDC BEDE BEE0 BEE2 BEE4 BEE6 BEE8 BEEA BEEC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_CalcScore(void)
{
    volatile int t;

    t = HistStart;
    t = HistCnt;
    t = TotalEggsLaidB;
    t = TotalEggsDiedB;
    t = BlackLost;
    t = RedLost;
    t = CurGameType;
    t = BColoniesStarted;
    t = RColoniesStarted;
    t = BColoniesKilled;
}

void DoWinHelp(unsigned int context)
{
    WinHelp(rootWnd, helpFile, 1, (unsigned long)(context & 0xff00));
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_DrawScoreWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words BEEE BEF0 BEF2; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_DrawScoreWindow(void)
{
    volatile int t;

    t = OverallScore;
    t = MiscStrs;
    t = ScenarioNameStrs;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ScoreDialog.
 * It only reproduces the object's selector-pool allocation order for the
 * words BEF4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ScoreDialog(void)
{
    volatile int t;

    t = *(int far *)&WindPromptStrs;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawCastePopUp.
 * It only reproduces the object's selector-pool allocation order for the
 * words BEF6 BEF8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawCastePopUp(void)
{
    volatile int t;

    t = (int)GamePaused;
    t = LessonTemp;
}

void far SetDefaultWindPrompt(int mode)
{
    if (GamePaused == 0)
        EditMessage(0L, -2, -1, mode);
    else if (CurGameTool == -1)
        EditMessage(WindPromptStrs->yardPrompt, -2, -1, mode);
    else if (CurGameTool == 10)
        EditMessage(WindPromptStrs->toolTenPrompt, -2, -1, mode);
    else if (CurGameTool == 11)
        EditMessage(WindPromptStrs->toolElevenPrompt, -2, -1, mode);
}

void far PictStrnDialog(int picture, int object, int force)
{
    int count;
    char far * far *strings;

    if (force != 0 || OptionStates[3] != 0) {
        StopSimulation();
        count = 0;
        strings = LoadStringAnt(object);
        if (strings) {
            while (strings[count] != 0)
                count++;
        }
        PictureDialog(strings, count, picture, force);
        if (strings) {
            free(strings);
            db_PurgeObject(object, 4);
        }
        RestartSimulation();
    }
}

void far win_DrawPictureWindow(int flags)
{
    struct WinRect rect;
    struct BitmapSize size;
    int fontHeight;
    int x;
    int i;

    if (!(flags & 2))
        return;

    win_GetObjRect(0x1e00, &rect);

    if (pictureBitmap == 0) {
        rect.top += 2;
    } else {
        gr_BitMapSize(&size, pictureBitmap);
        x = (rect.left + rect.right - size.width) / 2;
        win_DrawBitMap(x, rect.top, pictureBitmap);
        rect.top += size.height + 2;
    }

    font_SetFont(4);
    fontHeight = font_FontHeight();
    win_SetColorFromObjNum(0x1e01);

    for (i = 0; i < pictureLineCount; i++) {
        rect.bottom = rect.top + fontHeight;
        gr_CenterStrInRect(&rect, pictureLines[i]);
        rect.top += fontHeight;
    }
}

