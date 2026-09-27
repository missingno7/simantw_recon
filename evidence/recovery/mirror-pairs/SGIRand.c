/* Derived mechanically from the mirrored colony function _SGRand (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped SGRand->SGIRand; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * SGRand samples the same seed twice through the module-local SRand1 helper
 * and returns the smaller sample.  The target keeps the argument in DI and
 * compares the two generated signed-word results before returning.
 */
extern int near SRand1(int seed);

int SGIRand(register int seed)
{
    int value;

    value = seed;
    seed = SRand1(value);
    value = SRand1(value);
    return value <= seed ? value : seed;
}
