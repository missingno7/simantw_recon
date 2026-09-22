/*
 * SetAlarmDropState: enter or leave the alarm-pheromone drop mode.  When
 * turning it on, only a player on the surface plane (MePlane 1) in the
 * normal mode (MeMode 0) may do so: the layer mode is reset, the alarm
 * button object 0x10 is shown selected, MeDropAlarm is set and, unless
 * quiet, the confirm sound plays.  Otherwise, unless quiet, the refusal
 * sound plays.  Turning it off clears MeDropAlarm, deselects the button,
 * sets the layer mode to -1 and plays the confirm sound unless quiet.  In
 * every case the whole edit map is invalidated.
 */
extern int near MePlane;
extern int near ELayerMode;
extern int far MeMode;
extern int far MeDropAlarm;
extern int far EditRows;
extern int far EditColumns;

extern void far win_SetObjSelectedState(int object, int selected);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far InvalEuMap(int left, int top, int right, int bottom);

void far SetAlarmDropState(int state, int quiet)
{
    if (state != 0) {
        if (MePlane == 1 && MeMode == 0) {
            ELayerMode = 0;
            win_SetObjSelectedState(0x10, state);
            MeDropAlarm = 1;
            if (quiet == 0)
                myBeginSound(0xf, 0, 0x7e);
        } else if (quiet == 0)
            myBeginSound(1, 0, 0x7e);
    } else {
        MeDropAlarm = 0;
        win_SetObjSelectedState(0x10, state);
        ELayerMode = -1;
        if (quiet == 0)
            myBeginSound(0xf, 0, 0x7e);
    }
    InvalEuMap(0, 0, EditColumns, EditRows);
}
