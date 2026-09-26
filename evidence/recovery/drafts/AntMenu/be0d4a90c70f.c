/*
 * AntMenu: pop the ant/yellow-jacket context menu for a mouse event
 * (far MouseEvent pt, fields x@+8,y@+0xa) and run the selected
 * command.  Logs "ANTMENU".  If MeMode==0, uses menu 0x800 when
 * MeType==0x40 and no nest browse is in progress, else menu 0x700; if
 * MeMode==1, menu 0x2000; MeMode>=2 makes no selection (-1).  The
 * chosen ProxMenu item index looks up a game command from one of
 * three private tables depending on MeMode/MeType/MeNestStarted, and
 * command 2 additionally sends YellowCommand(3) when Shift is held.
 * Returns the raw ProxMenu selection (or -1).
 */
struct MouseEvent {
    int pad[4];
    int x;
    int y;
};

extern int far MeMode;
extern int near MeType;
extern int far MeNestStarted;

static signed char near cmdA[4] = {0x08, 0x09, 0x00, 0x00};
static signed char near cmdB[6] = {0x01, 0x02, 0x04, 0x05, 0x06, 0x00};
static signed char near cmdC[4] = {0x0a, 0x0b, 0x06, 0x00};

extern void far WinPrintf(char far *text);
extern int far win_DoProxMenu(int menu, int layer, int x, int y);
extern int far pascal GetAsyncKeyState(int key);
extern void far YellowCommand(int command);

int far AntMenu(struct MouseEvent far *pt)
{
    int cmd;
    int result;
    struct ModeSlot { int far *value; } mode;

    WinPrintf("ANTMENU");
    mode.value = &MeMode;

    if (*mode.value == 0) {
        if (MeType == 0x40 && MeNestStarted == 0)
            result = win_DoProxMenu(0x800, -1, pt->x, pt->y);
        else
            result = win_DoProxMenu(0x700, -1, pt->x, pt->y);
    } else if (*mode.value == 1) {
        result = win_DoProxMenu(0x2000, -1, pt->x, pt->y);
    } else {
        result = -1;
    }

    if (result < 0)
        return result;

    if (*mode.value == 1)
        cmd = cmdA[result];
    else if (MeType == 0x40 && MeNestStarted == 0)
        cmd = cmdB[result];
    else
        cmd = cmdC[result];

    if (cmd == 2) {
        if (GetAsyncKeyState(0x10) & 0x8000)
            cmd = 3;
            YellowCommand(cmd);
    }
    return result;
}
