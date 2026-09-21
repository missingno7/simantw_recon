/*
 * SetUserButton: install a user button's up/down bitmaps (button + fixed
 * bitmap bases 0x3889/0x3857, matching win_SetButtonBitmaps's signature),
 * lock the window object, fetch its WinButtonObject record and, for
 * button codes 0..15, toggle two flag bytes at +0x24/+0x25 (opposite
 * bit3 sense for the "live state" cases versus everything else) and
 * push the matching reflected state through win_SetObjSelectedState:
 * case 4 -> showTrails (selector 0xbe72/seg10), case 5 -> GamePaused
 * (selector 0xbe6e/seg9), cases 7,9,10,11,12,13 -> OptionStates[1,2,5,
 * 0,3,4] (selector 0xbe70/seg8) -- the same dense-switch family and
 * OptionStates ordering as the admitted DoUserButtonUpdate/
 * UpdateUserButtons. Out-of-range button (>15 unsigned) skips the
 * switch and the trailing win_SetObjSelectedState/win_UnlockWin pair
 * entirely, matching the observed bound check with no unlock on that
 * path.
 */
struct WinButtonObject {
    unsigned char reserved1[0x24];
    unsigned char flags1;
    unsigned char flags2;
};

extern int far showTrails;
extern int far GamePaused;
extern int far OptionStates[];
extern void far win_SetButtonBitmaps(int objectNumber, unsigned int bitmapUp,
                                     unsigned int bitmapDown);
extern void far win_LockWin(int objectNumber);
extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);
extern void far win_SetObjSelectedState(int object, int selected);
extern void far win_UnlockWin(int objectNumber);

void far SetUserButton(int object, int button)
{
    struct WinButtonObject far *obj;
    int state;

    win_SetButtonBitmaps(object, button + 0x3889, button + 0x3857);
    win_LockWin(object);
    obj = win_ObjAddr(object);
    switch (button) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 6:
    case 8:
    case 14:
    case 15:
        obj->flags1 &= ~8;
        obj->flags2 |= 8;
        state = 0;
        break;
    case 4:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        state = showTrails;
        break;
    case 5:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        state = GamePaused;
        break;
    case 7:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        state = OptionStates[1];
        break;
    case 9:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        state = OptionStates[2];
        break;
    case 10:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        state = OptionStates[5];
        break;
    case 11:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        state = OptionStates[0];
        break;
    case 12:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        state = OptionStates[3];
        break;
    case 13:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        state = OptionStates[4];
        break;
    default:
        return;
    }
    win_SetObjSelectedState(object, state);
    win_UnlockWin(object);
}
