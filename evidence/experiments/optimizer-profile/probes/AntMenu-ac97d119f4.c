/*
 * AntMenu: pop the ant context menu for a mouse event (far event record,
 * x at +8, y at +0xa) and dispatch the chosen command.  Traces "ANTMENU".
 * In MeMode 0 the menu is 0x800 when the player is a yellow jacket
 * (MeType 0x40) whose nest has not started, otherwise 0x700; in MeMode 1
 * it is 0x2000; other modes select nothing (-1).  A selection >= 0 is
 * translated through one of three private signed-byte command tables
 * (DGROUP 0x1ba6: 08 09 00 00, 0x1baa: 01 02 04 05 06 00, 0x1bb0: 0a 0b
 * 06 00, followed by the "ANTMENU" literal) chosen by the same
 * MeMode/MeType/MeNestStarted test; outside MeMode 1, command 2 becomes
 * command 3 while Shift (VK 0x10) is held.  The command goes to
 * YellowCommand and the raw menu selection is returned.
 *
 * Unit profile /Og: MeMode is read through a far pointer local homed on
 * the frame (reloaded via LES); the three win_DoProxMenu calls share one
 * cross-jumped call site.  The selection is copied into the command
 * variable (SI) and translated in place.
 */
struct MouseEvent {
    int pad[4];
    int x;
    int y;
};

extern int far MeMode;
extern int near MeType;
extern int far MeNestStarted;

static signed char near yellowCmds[4] = {0x08, 0x09, 0x00, 0x00};
static signed char near antCmds[6] = {0x01, 0x02, 0x04, 0x05, 0x06, 0x00};
static signed char near mapCmds[4] = {0x0a, 0x0b, 0x06, 0x00};

extern void far WinPrintf(char far *format, ...);
extern int far win_DoProxMenu(int menu, int layer, int x, int y);
extern int far pascal GetAsyncKeyState(int key);
extern void far YellowCommand(int command);

int far AntMenu(struct MouseEvent far *pt)
{
    int result;
    int cmd;
    int far *mode = &MeMode;

    WinPrintf("ANTMENU");

    if (*mode == 0) {
        if (MeType == 0x40 && MeNestStarted == 0)
            result = win_DoProxMenu(0x800, -1, pt->x, pt->y);
        else
            result = win_DoProxMenu(0x700, -1, pt->x, pt->y);
    } else if (*mode == 1) {
        result = win_DoProxMenu(0x2000, -1, pt->x, pt->y);
    } else {
        result = -1;
    }

    if (result < 0)
        return result;

    cmd = result;
    if (*mode == 1) {
        cmd = mapCmds[cmd];
    } else {
        if (MeType == 0x40 && MeNestStarted == 0)
            cmd = yellowCmds[cmd];
        else
            cmd = antCmds[cmd];
        if (cmd == 2 && (GetAsyncKeyState(0x10) & 0x8000))
            cmd = 3;
    }
    YellowCommand(cmd);
    return result;
}
