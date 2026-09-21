/*
 * Hypothesis: set the yellow ant's requested plane and goal coordinates.
 * A zero plane is normalized to plane 1.  The crazy counter is reset, and
 * only the upper edge of a low-y goal is clamped from x=63 or greater to 62;
 * nonpositive x is normalized to 1 without a second global write.
 */
extern int far MeGoalPlane;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far MeCrazyCnt;

void far SetGoalsY(int plane, int x, int y)
{
    MeGoalPlane = plane ? plane : 1;

    MeGoalX = x;
    MeGoalY = y;
    MeCrazyCnt = -2;

    if (plane >= 2 && y < 2) {
        if (x > 0) {
            if (x >= 0x3f) {
                x = 0x3e;
                MeGoalX = x;
            }
        } else {
            x = 1;
        }
    }
}
