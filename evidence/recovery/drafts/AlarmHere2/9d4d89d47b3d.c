/*
 * AlarmHere2 raises one byte in the Dx8 alarm grid, addressed by the
 * half-resolution coordinates.  Existing stronger values are preserved;
 * otherwise the requested low-byte level replaces the cell.
 */
extern int far Dx8;

void near AlarmHere2(int x, int y, volatile int level)
{
    if (((unsigned char far *)&Dx8)[0x52d2 + (x >> 1) * 0x20 + (y >> 1)] <= level)
        ((unsigned char far *)&Dx8)[0x52d2 + (x >> 1) * 0x20 + (y >> 1)] = (unsigned char)level;
}
