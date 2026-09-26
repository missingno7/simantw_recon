/* Check the completion condition selected by the current tutorial lesson.
 * PACK objects supply the lesson timer, counters, map point and alarm flags. */
struct MapPoint {
    int x;
    int y;
};

extern unsigned char near MapA[];
extern int near MapPlane;
extern int near MeHealth;
extern int near MeLocX;
extern int near MeLocY;
extern int near MePlane;
extern int near MeType;
extern int near YardMode;
extern int far MeMoveMe;
extern int far MeDis;
extern int far MeDropAlarm;
extern int far TilesDugB;
extern long far TimeTemp;
extern int far LessonTemp;
extern int far modeLevels[2];
extern int far ModePopB[6];
extern struct MapPoint far MapPnt;
extern long far MacTickCount(void);
extern int far win_IsWinInFront(int window);
extern void far SetAlarmDropState(int state, int quiet);

int far LessonDone(int lesson)
{
    switch (lesson - 1) {
    case 0:
    case 1:
    case 5:
    case 10:
    case 14:
    case 16:
    case 22:
    case 24:
    case 27:
    case 28:
    case 30:
    case 33:
    case 34:
    case 36:
    case 39:
    case 43:
    case 44:
    case 47:
    case 50:
    case 52:
    case 54:
    case 55:
        return 1;

    case 2:
    case 3:
        if ((long)TilesDugB > TimeTemp && MeMoveMe == 0)
            return 1;
        return 0;

    case 6:
    case 25:
        if (MeLocY + MeLocX != LessonTemp && MeDis == 0 &&
            MacTickCount() > TimeTemp)
            return 1;
        return 0;

    case 8:
        if (MapPnt.x + MapPnt.y != LessonTemp)
            return 1;
        if (MacTickCount() > TimeTemp)
            return 1;
        return 0;

    case 9:
    case 31:
    case 41:
        if (win_IsWinInFront(0x0100))
            return 1;
        return 0;

    case 12:
        if (MePlane == 1 && MapA[MeLocY + (MeLocX << 6)] > 0x47)
            return 1;
        return 0;

    case 13:
        if (MeHealth > 0x5a)
            return 1;
        return 0;

    case 15:
        if (MeType == 0x18)
            return 1;
        return 0;

    case 17:
        if (MePlane == 2)
            return 1;
        return 0;

    case 4:
    case 19:
        if (MePlane == 1)
            return 1;
        return 0;

    case 18:
    case 21:
        if (MeType == 0x10)
            return 1;
        return 0;

    case 20:
        if (MeType == 0x28)
            return 1;
        return 0;

    case 23:
        if (ModePopB[5] > 1)
            return 1;
        return 0;

    case 26:
        if (MeLocY + MeLocX != LessonTemp && MeDropAlarm != 0 &&
            MeDis == 0)
            return 1;
        return 0;

    case 29:
        if (MeDropAlarm != 0)
            SetAlarmDropState(0, 1);
        if (LessonTemp != 0)
            return 1;
        return 0;

    case 7:
    case 42:
    case 45:
    case 49:
        if (LessonTemp != 0)
            return 1;
        return 0;

    case 32:
    case 37:
        if (MapPlane == 1)
            return 1;
        return 0;

    case 35:
        if (YardMode == 1)
            return 1;
        return 0;

    case 38:
        if (win_IsWinInFront(0x1200))
            return 1;
        return 0;

    case 40:
        if (modeLevels[0] + modeLevels[1] != LessonTemp)
            return 1;
        return 0;

    case 46:
        if (win_IsWinInFront(0x1300))
            return 1;
        return 0;

    case 11:
    case 48:
        if (win_IsWinInFront(0))
            return 1;
        return 0;

    case 51:
        if (ModePopB[5] > 0x28)
            return 1;
        return 0;

    case 53:
        if (MePlane == 3) {
            LessonTemp = 0;
            return 1;
        }
        if (MePlane == 2) {
            LessonTemp = 1;
            return 1;
        }
        return 0;
    }
    return 0;
}
