/*
 * Hypothesis: choose the requested health unless NeverHungry forces 100,
 * reset the countdown for positive health, clamp to [0,100], then commit the
 * health and set WantFood according to the warning threshold.  MeHealth is
 * DGROUP data; the other state objects are far data in the observed modules.
 */
extern int far NeverHungry;
extern int far MeHealthCntDwn;
extern int far MeWarnHealth;
extern int far MeWantFood;
extern int near MeHealth;

void far SetMyHealth(int health)
{
    int value;

    if (NeverHungry)
        value = 100;
    else
        value = health;

    if (value > 0)
        MeHealthCntDwn = 0;

    if (value > 100)
        value = 100;
    if (value < 0)
        value = 0;

    if (MeWarnHealth < value) {
        if (value >= 10) {
            MeHealth = value;
            MeWantFood = 0;
        }
    } else {
        MeHealth = value;
        MeWantFood = 1;
    }
}
