/*
 * Hypothesis: choose a 64- or 128-pixel horizontal edit bound from MapPlane,
 * clamp the far match_position x coordinate using editWidth, then clamp y to
 * the 64-pixel edit area using editHeight.  Negative y is normalized and
 * returns immediately, matching the target's short second-path return.
 */
extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int far match_position[];

void far BoundEditPosition(void)
{
    int limit;

    if (MapPlane < 0)
        return;
    if (MapPlane <= 1)
        limit = 0x80;
    else
        limit = 0x40;

    if (match_position[0] < 0)
        match_position[0] = 0;
    else if (match_position[0] + editWidth > limit)
        match_position[0] = limit - editWidth;

    if (match_position[1] < 0) {
        match_position[1] = 0;
        return;
    }
    if (match_position[1] + editHeight > 0x40)
        match_position[1] = 0x40 - editHeight;
}
