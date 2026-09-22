/* Derived mechanically from the mirrored colony function _KillTailB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped KillTailB->KillTailR, LifeB->LifeR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * KillTailB clears the tail's local occupancy byte, reads its direction byte
 * and 8-bit map row from the far Dx8 table, and clears the corresponding
 * 64-wide LifeB entry.  The low-byte mask is intentional: the historical
 * routine converts the stored word row into a row offset before indexing.
 */
extern unsigned char far Dx8[];
extern unsigned char near LifeR[];

void KillTailR(int tail)
{
    unsigned char direction;
    unsigned int row;

    Dx8[tail + 0x46E6] = 0;
    direction = Dx8[tail + 0x42FA];
    row = *(unsigned int far *)(Dx8 + tail + 0x4104);
    row &= 0xff;
    row <<= 6;
    LifeR[row + direction] = 0;
}
