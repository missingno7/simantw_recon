/* Draft: InitApplicationWindows */
typedef void (far *Hook)(void);

extern void far win_LoadAllWindows(void);
extern void win_SetWinDrawHook(int id, Hook f);
extern void far InitMapFunctions(void);

extern void far win_DrawEditWindow(void);
extern void far win_DrawMapWindow(void);
extern void far win_DrawHistoryWindow(void);
extern void far win_DrawModeWindow(void);
extern void far win_DrawCasteWindow(void);
extern void far win_DrawYardWindow(void);
extern void far win_DrawInfoWindow(void);
extern void far win_DrawPictureWindow(void);
extern void far win_DrawEndGameWindow(void);
extern void far win_DrawExamineWindow(void);
extern void far win_DrawScoreWindow(void);

void InitApplicationWindows(void)
{
    win_LoadAllWindows();
    win_SetWinDrawHook(0x000, (Hook)win_DrawEditWindow);
    win_SetWinDrawHook(0x100, (Hook)win_DrawMapWindow);
    win_SetWinDrawHook(0x1500, (Hook)win_DrawHistoryWindow);
    win_SetWinDrawHook(0x1200, (Hook)win_DrawModeWindow);
    win_SetWinDrawHook(0x1300, (Hook)win_DrawCasteWindow);
    win_SetWinDrawHook(0x1900, (Hook)win_DrawYardWindow);
    win_SetWinDrawHook(0x500, (Hook)win_DrawInfoWindow);
    win_SetWinDrawHook(0x1e00, (Hook)win_DrawPictureWindow);
    win_SetWinDrawHook(0x400, (Hook)win_DrawEndGameWindow);
    win_SetWinDrawHook(0x1d00, (Hook)win_DrawExamineWindow);
    win_SetWinDrawHook(0x1800, (Hook)win_DrawScoreWindow);
    InitMapFunctions();
}
