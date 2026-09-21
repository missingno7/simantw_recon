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
    if (NeverHungry)
        health = 100;

    if (health > 0)
        MeHealthCntDwn = 0;

    if (health > 100)
        health = 100;
    if (health < 0)
        health = 0;

    if (MeWarnHealth >= health) {
        MeHealth = health;
        MeWantFood = 1;
    } else if (health >= 10) {
        MeHealth = health;
        MeWantFood = 0;
    }
}
