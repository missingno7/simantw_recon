/*
 * DoUserButtonUpdate: reflect the state word of user button 5..13 in the
 * ribbon: object 5 shows the far PACK word GamePaused (MAPSYM 0x9c28)
 * (own selector slot 0xbe6e), objects 7..13 show OptionStates[1..5]
 * through win_SetObjSelectedState; objects 6, 8 (and out of range) do
 * nothing. A dense switch dispatched through a cs: jump table.
 */
extern int far GamePaused;
extern int far OptionStates[];
extern void far win_SetObjSelectedState(int object, int selected);

void far DoUserButtonUpdate(int button, int object)
{
    switch (button) {
    case 5:
        win_SetObjSelectedState(object, GamePaused);
        break;
    case 7:
        win_SetObjSelectedState(object, OptionStates[1]);
        break;
    case 9:
        win_SetObjSelectedState(object, OptionStates[2]);
        break;
    case 10:
        win_SetObjSelectedState(object, OptionStates[5]);
        break;
    case 11:
        win_SetObjSelectedState(object, OptionStates[0]);
        break;
    case 12:
        win_SetObjSelectedState(object, OptionStates[3]);
        break;
    case 13:
        win_SetObjSelectedState(object, OptionStates[4]);
        break;
    }
}
