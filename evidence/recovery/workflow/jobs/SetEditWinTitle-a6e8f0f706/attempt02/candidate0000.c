/* SetEditWinTitle: set the edit window's title-bar text (object 1). If no
 * caller-supplied string is given, build a default title in a local buffer
 * by concatenating a short literal with a MiscStrs entry and the scenario
 * name string indexed by CurGameType, then use that buffer. Finally, if the
 * edit window (object 0) is open, redraw its title inside a pushed clip
 * (same clip_Push/clip_SetWin/.../clip_Pop shape as SetMapTitle). */
extern void far win_SetObjFormatStr(int object, char far *text);
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far win_DrawTitle(int object);

extern char far * far * far MiscStrs;
extern char far * far * far ScenarioNameStrs;
extern int far CurGameType;

void far SetEditWinTitle(char far *text)
{
    char buf[80];

    if (text == 0) {
        char far *d;
        char far *s;

        strcpy(buf, "SimAnt");

        d = buf;
        while (*d)
            d++;
        s = MiscStrs[15];
        while (*d++ = *s++)
            ;

        d = buf;
        while (*d)
            d++;
        s = ScenarioNameStrs[CurGameType];
        while (*d++ = *s++)
            ;

        text = buf;
    }

    win_SetObjFormatStr(1, text);

    if (win_IsWinOpen(0)) {
        clip_Push();
        clip_SetWin(0);
        win_DrawTitle(1);
        clip_Pop();
    }
}
