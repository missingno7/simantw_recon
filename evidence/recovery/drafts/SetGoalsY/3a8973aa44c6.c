extern int far MeGoalPlane;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far MeCrazyCnt;
/* Preserve the original plane in the clamp test and normalize through a local copy. */
void far SetGoalsY(int plane, int x, int y)
{
    int storedPlane;
    storedPlane = plane;
    if (storedPlane == 0) storedPlane = 1;
    MeGoalPlane = storedPlane;
    MeGoalX = x;
    MeGoalY = y;
    MeCrazyCnt = -2;
    if (plane >= 2 && y < 2) {
        if (x <= 0) MeGoalX = 1;
        else if (x >= 63) MeGoalX = 62;
    }
}
