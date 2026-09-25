/*
 * Window-library selection state: two byte flags followed by the selected
 * window/object handles and library/resource words, all initially clear
 * except the selected-window sentinel (-1).
 */
char near win_initted = 0;
char near win_changed = 0;
int near win_winSelected = -1;
int near win_objSelected = 0;
int near win_libVersion = 0;
int near win_RESEDFlag = 0;
