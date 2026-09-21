/*
 * Hypothesis: set the yellow ant's requested plane and goal coordinates.
 * A zero plane is normalized to plane 1.  The crazy counter is reset, and
 * only the upper edge of a low-y goal is clamped from x=63 or greater to 62;
 * nonpositive x is normalized to 1 without a second global write.
 */
extern int far MeGoalPlane[1];
extern int far MeGoalX[1];
extern int far MeGoalY[1];
extern int far MeCrazyCnt[1];

void far SetGoalsY(int plane, int x, int y)
{
    MeGoalPlane[0] = plane ? plane : 1;

    MeGoalX[0] = x;
    MeGoalY[0] = y;
    MeCrazyCnt[0] = -2;

    if (plane >= 2 && y < 2) {
        if (x > 0) {
            if (x >= 0x3f) {
                x = 0x3e;
                MeGoalX[0] = x;
            }
        } else {
            x = 1;
        }
    }
}
