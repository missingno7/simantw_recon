/* Derived mechanically from the mirrored colony function _KillTailR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped KillTailR->KillTailB, LifeR->LifeB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * KillTailR clears the tail's local occupancy byte, reads its direction byte
 * and 8-bit map row from the far Dx8 table, and clears the corresponding
 * 64-wide LifeR entry.  The row is deliberately reduced to its low byte
 * before the six-bit row stride is applied.
 */
extern unsigned char far Dx8[];
extern unsigned char near LifeB[];

void KillTailB(int tail)
{
    unsigned char direction;
    unsigned int row;

    Dx8[tail + 0x46e6] = 0;
    direction = Dx8[tail + 0x42fa];
    row = *(unsigned int far *)(Dx8 + tail + 0x4104);
    row &= 0xff;
    row <<= 6;
    LifeB[row + direction] = 0;
}
