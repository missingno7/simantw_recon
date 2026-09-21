/*
 * GstrB: rate the black colony's strategic situation as 0..5.  With health
 * below 10, an enemy population above half the black population (while
 * red has queens) is hopeless (0); otherwise health below 30 rates 5 and
 * below 50 rates 4.  Fewer dug tiles than ants rates 3, fewer than twice
 * the ants rates 2; a large colony (over 100) facing red queens whose
 * population exceeds a third of its own again rates 0, and everything
 * else rates 1.  The far PACK counters are read through immediate
 * segment loads while the near DGROUP words are read through SS.
 */
extern int near HealthB;
extern int near BpopT;
extern int near RpopT;
extern int far RedQueens;
extern int far TilesDugB;
#define QUEENS RedQueens
#define DUG TilesDugB

int far GstrB(void)
{
#define HEALTH health
    register int health = HealthB;
    if (HEALTH < 10) {
        if ((BpopT >> 1) > RpopT && RpopT > 0 && QUEENS > 0)
            return 0;
    }
    if (HEALTH < 30)
        return 5;
    if (HEALTH < 50)
        return 4;
    if (DUG < BpopT)
        return 3;
    if (DUG < BpopT * 2)
        return 2;
    if (BpopT > 100 && RpopT > 0 && QUEENS > 0 && BpopT / 3 > RpopT)
        return 0;
    return 1;
}
