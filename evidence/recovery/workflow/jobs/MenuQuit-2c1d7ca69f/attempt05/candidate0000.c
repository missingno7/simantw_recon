/*
 * Ask whether the current game should be saved before quitting.  The
 * private flag prevents a second prompt once the menu has accepted the quit;
 * Cancel returns false, Yes retries after a successful SaveGame, and No (or
 * a failed save) selects the corresponding historical return path.
 */
extern int near rootWnd;
extern int near menuQuitFlag;
extern int far pascal MessageBox(int window, char far *text,
                                  char far *caption, unsigned style);
extern int far SaveGame(int mode);

int MenuQuit(void)
{
    if (menuQuitFlag == 0) {
        switch (MessageBox(rootWnd, "Do you want to save ",
                           "SimAnt Quit", 0x1123)) {
        case 2:
            goto cancel_quit;
        default:
            goto mark_quit;
        case 6:
            goto save_game;
        }

mark_quit:
        menuQuitFlag = 1;
        return 1;

save_game:
        if (SaveGame(0) != 0)
            goto mark_quit;

cancel_quit:
        return 0;
    }
    return 1;
}
