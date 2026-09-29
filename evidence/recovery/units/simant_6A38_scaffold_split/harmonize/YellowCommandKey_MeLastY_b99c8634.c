/*
 * YellowCommandKey: translate a WM_CHAR-style key code for the yellow
 * (player) ant into a YellowCommand() action; returns 1 if the key was
 * handled, 0 otherwise.  Most letters/digits just push a fixed command
 * code (uppercase and lowercase/digit aliases share a body: X/x -> 6,
 * J/j -> 12 gated on Tab being held and MeMode==1, 1/a, 2/b, 3/c, 4/d and
 * 0/` each select a command, with the 1/a and 2/b bodies additionally
 * consulting MeMode/MeType/MeNestStarted and (for 2/b) the Ctrl key to
 * choose between two or three related commands).  Backspace either jumps
 * to the yellow ant (Shift held) or -- depending on MeMode -- either
 * resets a whole family of unnamed match_position slots to their
 * cleared/sentinel values (MeMode==0 and the match_position "busy" slot
 * at 0x7d24 is set) or recentres/updates the Suser* snapshot before
 * calling CenterAnt (MeMode==1).  '$' just beeps via myBeginSound.  Any
 * other key returns 0.
 */
extern int near MeType;
extern int near MeLocX;
extern int near MeLocY;
extern int near MePlane;
extern int far MeMode;
extern int far MeNestStarted;
extern int far SuserX;
extern int far SuserY;
extern int far SMode;
extern int far MeGoalPlane;
extern int far MeLastX;
extern int far MeGoalX;
extern int far MeGoalPlane, MeLastX, MeGoalX, MeLastY, MeGoalY;
extern int far MeGoalY;
extern int far MeCmd;
extern int far MeMoveMe;
extern int far MeDis;
extern int far MePrevDis;
extern int far MeSteps;
extern int far MeCrazyCnt;

extern int far pascal GetKeyState(int key);
extern void far YellowCommand(int cmd);
extern void far GotoMyAnt(void);
extern void far CenterAnt(void);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

int far YellowCommandKey(int key)
{
    int retval = 1;

    switch (key) {
    case 'x':
    case 'X':
        YellowCommand(6);
        break;

    case 'J':
    case 'j':
        if (GetKeyState(9) & 0x8000) {
            if (MeMode == 1)
                YellowCommand(0xc);
        } else {
            retval = 0;
        }
        break;

    case '1':
    case 'a':
        if (MeMode != 0)
            YellowCommand(0xa);
        else if (MeType != 0x40 || MeNestStarted != 0)
            YellowCommand(1);
        else
            YellowCommand(8);
        break;

    default: {
        int *resultAddress = &retval;
        retval = 0;
        return *resultAddress;
    }

    case 8:
        if (GetKeyState(0x10) & 0x8000) {
            GotoMyAnt();
            return retval;
        }
        if (MeMode == 0) {
            if (MeMoveMe != 0) {
                MeGoalPlane = MePlane;
                MeLastX = MeLocX;
                MeGoalX = MeLocX;
                MeLastY = MeLocY;
                MeGoalY = MeLocY;
                MeCmd = 0;
                MeMoveMe = 0;
                MeDis = 0;
                MePrevDis = 0;
                MeSteps = 0;
                MeCrazyCnt = 0xfffe;
                break;
            }
            goto centerFromModes;
        }
        if (MeMode == 1) {
            if (SuserX != MeLocX || SuserY != MeLocY) {
                SuserX = MeLocX;
                SuserY = MeLocY;
                SMode = 0;
                break;
            }
        centerFromModes:
            CenterAnt();
            break;
        }
        break;

    case 0x24:
        myBeginSound(0xf, 0, 0x7e);
        break;

    case 0x32:
    case 'b':
        if (MeMode != 0)
            YellowCommand(0xb);
        else if (MeType != 0x40 || MeNestStarted != 0) {
            if (GetKeyState(0x11) & 0x8000)
                YellowCommand(3);
            else
                YellowCommand(2);
        } else
            YellowCommand(9);
        break;

    case 0x33:
    case 'c':
        YellowCommand(4);
        break;

    case 0x34:
    case 'd':
        YellowCommand(5);
        break;

    case 0x30:
    case '`':
        YellowCommand(7);
        break;

    }

    return retval;
}
