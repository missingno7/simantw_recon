/*
 * UpdateUserButtons: refresh both the map-window and yard-window user
 * button ribbons from the parallel state tables mapUserButton[]/
 * yardUserButton[] (MAPSYM _mapUserButton at DGROUP:0x12, _yardUserButton
 * immediately after it at DGROUP:0x22, 8 words each -- the same
 * cmp/ja/shl/xchg/jmp cs:[bx+T] dense-switch idiom as the already
 * admitted DoUserButtonUpdate, with case values 5,7,9,10,11,12,13
 * dispatching to the far PACK word GamePaused (selector 0xbe6e) and
 * OptionStates[] (selector 0xbe70), holes falling through to nothing.
 * Two private DATA-segment guard words (below _edata) gate the whole
 * refresh: if neither window has pending button state, skip the loop.
 * Object ids for win_SetObjSelectedState are literal per-window bases
 * (map buttons start at 0x2210, yard buttons at 0x230b) offset by the
 * loop index, matching the observed "lea ax,[si+BASE]" address-style
 * addition used in place of a plain add.
 */
extern int far GamePaused;
extern int far OptionStates[];
extern void far win_SetObjSelectedState(int object, int selected);
extern int near mapUserButton[8];
extern int near yardUserButton[8];

static int near mapButtonsPending = 0;
static int near yardButtonsPending = 0;

void far UpdateUserButtons(void)
{
    int i;

    if (mapButtonsPending || yardButtonsPending) {
        for (i = 0; i < 8; i++) {
            switch (mapUserButton[i]) {
            case 5:
                win_SetObjSelectedState(0x2210 + i, GamePaused);
                break;
            case 7:
                win_SetObjSelectedState(0x2210 + i, OptionStates[1]);
                break;
            case 9:
                win_SetObjSelectedState(0x2210 + i, OptionStates[2]);
                break;
            case 10:
                win_SetObjSelectedState(0x2210 + i, OptionStates[5]);
                break;
            case 11:
                win_SetObjSelectedState(0x2210 + i, OptionStates[0]);
                break;
            case 12:
                win_SetObjSelectedState(0x2210 + i, OptionStates[3]);
                break;
            case 13:
                win_SetObjSelectedState(0x2210 + i, OptionStates[4]);
                break;
            }
            switch (yardUserButton[i]) {
            case 5:
                win_SetObjSelectedState(0x230b + i, GamePaused);
                break;
            case 7:
                win_SetObjSelectedState(0x230b + i, OptionStates[1]);
                break;
            case 9:
                win_SetObjSelectedState(0x230b + i, OptionStates[2]);
                break;
            case 10:
                win_SetObjSelectedState(0x230b + i, OptionStates[5]);
                break;
            case 11:
                win_SetObjSelectedState(0x230b + i, OptionStates[0]);
                break;
            case 12:
                win_SetObjSelectedState(0x230b + i, OptionStates[3]);
                break;
            case 13:
                win_SetObjSelectedState(0x230b + i, OptionStates[4]);
                break;
            }
        }
    }
}
