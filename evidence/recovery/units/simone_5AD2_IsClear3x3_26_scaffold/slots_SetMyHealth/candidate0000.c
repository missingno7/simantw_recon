/*
 * SetMyHealth chooses the requested health unless NeverHungry forces 100
 * (the fall-through/health-branch precedes the forced-100 branch in the
 * target, so the source tests !NeverHungry first), resets the countdown
 * for positive health, clamps to [0,100] via an if/else-if chain (the
 * upper clamp jumps past the lower-bound test), then always commits the
 * health and only differs on WantFood: cleared when both above the warn
 * threshold and at least 10, set otherwise -- both branches converge on
 * the same MeHealth store, matching the shared target block.
 */
extern int far NeverHungry;
extern int far MeHealthCntDwn;
extern int far MeWarnHealth;
extern int far MeWantFood;
extern int near MeHealth;

void far SetMyHealth(int health)
{
    int value;

    if (!NeverHungry)
        value = health;
    else
        value = 100;

    if (value > 0)
        MeHealthCntDwn = 0;

    if (value > 100)
        value = 100;
    else if (value < 0)
        value = 0;

    if (MeWarnHealth < value && value >= 10) {
        MeHealth = value;
        MeWantFood = 0;
    } else {
        MeHealth = value;
        MeWantFood = 1;
    }
}
