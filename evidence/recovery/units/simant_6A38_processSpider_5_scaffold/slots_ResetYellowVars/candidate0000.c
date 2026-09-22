extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int far MeGoalPlane;
extern int far MeLastX;
extern int far MeLastY;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far MeCmd;
extern int far MeMoveMe;
extern int far MePrevDis;
extern int far MeDis;
extern int far MeSteps;
extern int far MeCrazyCnt;

void ResetYellowVars(int plane, int x, int y)
{
    MePlane = plane;
    MeGoalPlane = plane;
    MeLocX = x;
    MeLastX = x;
    MeGoalX = x;
    MeLocY = y;
    MeLastY = y;
    MeGoalY = y;
    MeCmd = 0;
    MeMoveMe = 0;
    MeDis = 0;
    MePrevDis = 0;
    MeSteps = 0;
    MeCrazyCnt = -2;
}
