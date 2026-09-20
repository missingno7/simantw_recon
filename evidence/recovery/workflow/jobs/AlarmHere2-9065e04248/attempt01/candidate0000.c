/*
 * AlarmHere2 raises one byte in the Dx8 alarm grid, addressed by the
 * half-resolution coordinates.  Existing stronger values are preserved;
 * otherwise the requested low-byte level replaces the cell.
 */
extern unsigned char far Dx8[];

void near AlarmHere2(int x, int y, int level)
{
    if (Dx8[0x52d2 + (x >> 1) * 0x20 + (y >> 1)] <= level)
        Dx8[0x52d2 + (x >> 1) * 0x20 + (y >> 1)] = (unsigned char)level;
}
