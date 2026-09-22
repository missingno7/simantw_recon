/* Derived mechanically from the mirrored colony function _GstrB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped BlkQueens->RedQueens, BpopT->RpopT, GstrB->GstrR, HealthB->HealthR, TilesDugB->TilesDugR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
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
extern int near HealthR;
extern int near RpopT;
extern int near RpopT;
extern int far RedQueens;
extern int far TilesDugR;
#define QUEENS RedQueens
#define DUG TilesDugR

int far GstrR(void)
{
#define HEALTH HealthR
    if (HEALTH < 10) {
        if ((RpopT >> 1) > RpopT && RpopT > 0 && QUEENS > 0)
            return 0;
    }
    if (HEALTH < 30)
        return 5;
    if (HEALTH < 50)
        return 4;
    if (DUG < RpopT)
        return 3;
    if (DUG < RpopT * 2)
        return 2;
    if (RpopT > 100 && RpopT > 0 && QUEENS > 0 && RpopT / 3 > RpopT)
        return 0;
    return 1;
}
