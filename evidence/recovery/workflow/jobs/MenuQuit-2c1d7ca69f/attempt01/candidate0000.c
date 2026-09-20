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
    int answer;

    if (menuQuitFlag != 0)
        return 1;

    for (;;) {
        answer = MessageBox(rootWnd, "Do you want to save ",
                            "SimAnt Quit", 0x1123);
        if (answer == 2)
            return 0;
        if (answer == 6) {
            if (SaveGame(0) != 0)
                return 0;
            continue;
        }
        menuQuitFlag = 1;
        return 1;
    }
}
