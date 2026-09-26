/* Candidate translation unit simant_B324_win_DrawModeWindow_2_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _win_DrawModeWindow, _win_DrawCasteWindow
 * SCAFFOLDED: unclaimed members _InitTriVars, _win_CasteControlChanged, _win_ModeControlChanged are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
struct FastBitmap {
    int width;
    int height;
};
extern int far modeAnimHandle;
extern int near modeBitmap;
extern unsigned char near displayType;
extern int near modeSet[];
extern void far clip_SetWin(int window);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far DoFastBitmap(int x, int y, int width, int height, char far *bits, int flags);
extern void far DoFastMonoBitmap(int x, int y, int width, int height, char far *bits);
extern void far DrawControlLevels(int window, int index, int level);
extern int far casteAnimHandle;
extern unsigned int near casteBitmap;

extern int far match_position;  /* scaffold reference for pool word C11C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C11E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C120 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far triHeight;  /* scaffold reference for pool word C122 (segment 9, MAPSYM_SITE_NAME) */
extern int far Scycle;  /* scaffold reference for pool word C124 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C126 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C128 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C12A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C12E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SMode;  /* scaffold reference for pool word C130 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word C132 (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_InitTriVars(void);
void far pool_stub_win_CasteControlChanged(void);
void far pool_stub_win_ModeControlChanged(void);
void far win_DrawCasteWindow(int flags);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitTriVars)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_CasteControlChanged)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_ModeControlChanged)
#pragma alloc_text(RUN2_TEXT, win_DrawCasteWindow)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitTriVars.
 * It only reproduces the object's selector-pool allocation order for the
 * words C11C C11E C120 C122 C124; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitTriVars(void)
{
    volatile int t;

    t = match_position;
    t = match_length;
    t = pack_buf;
    t = triHeight;
    t = Scycle;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_CasteControlChanged.
 * It only reproduces the object's selector-pool allocation order for the
 * words C126 C128 C12A C12C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_CasteControlChanged(void)
{
    volatile int t;

    t = EditColumns;
    t = MiscStrs;
    t = LastQueenPlane;
    t = (int)casteAnimHandle;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_ModeControlChanged.
 * It only reproduces the object's selector-pool allocation order for the
 * words C12E C130 C132 C134; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_ModeControlChanged(void)
{
    volatile int t;

    t = EditDragPnt;
    t = SMode;
    t = modeButtonState;
    t = (int)modeAnimHandle;
}

void far win_DrawModeWindow(int flags)
{
    struct WinRect rect;
    struct { int x, y; } pos;
    struct FastBitmap far *bits;

    if ((char)flags & 1) {
        if (modeAnimHandle == 0)
            clip_SetWin(0x1200);
    }
    if ((char)flags & 1) {
        if (modeBitmap != 0) {
            bits = (struct FastBitmap far *)mem_Lock(modeBitmap);
            win_GetObjRect(0x1202, &rect);
            pos.x = rect.left;
            pos.y = rect.top;
            if ((displayType & 1) == 0)
                DoFastBitmap(pos.x, pos.y, bits->width, bits->height, (char far *)(bits + 1), 0);
            else
                DoFastMonoBitmap(pos.x, pos.y, bits->width, bits->height, (char far *)(bits + 1));
            mem_Unlock(modeBitmap);
        }
    }
    if (flags & 2)
        DrawControlLevels(0x1200, 0, modeSet[9]);
}

void far win_DrawCasteWindow(int flags)
{
    struct WinRect rect;
    struct FastBitmap far *bits;
    struct { int x; int y; } pos;

    if ((char)flags & 1) {
        if (casteAnimHandle == 0)
            clip_SetWin(0x1300);
    }
    if ((char)flags & 1) {
        if (casteBitmap != 0) {
            bits = (struct FastBitmap far *)mem_Lock(casteBitmap);
            win_GetObjRect(0x1302, &rect);
            pos.x = rect.left;
            pos.y = rect.top;
            if ((displayType & 1) == 0)
                DoFastBitmap(pos.x, pos.y, bits->width, bits->height, (char far *)(bits + 1), 0);
            else
                DoFastMonoBitmap(pos.x, pos.y, bits->width, bits->height, (char far *)(bits + 1));
            mem_Unlock(casteBitmap);
        }
    }
    if (flags & 2)
        DrawControlLevels(0x1300, 0, modeSet[10]);
}

