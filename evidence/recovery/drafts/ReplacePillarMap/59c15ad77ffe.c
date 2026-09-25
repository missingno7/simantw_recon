/*
 * Hypothesis: after IsValidA accepts the coordinate, select the pillar
 * palette entry from the direction axis and replace the corresponding MapA
 * byte.  PillDir and PillarMap are far data in the pillar segment; MapA is
 * the near SimAnt map plane.
 */
extern unsigned char far PillDir;
extern unsigned char far PillarMap[];
extern unsigned char near MapA[];
extern int far IsValidA(int x, int y);

void far ReplacePillarMap(int x, int y)
{
    if (IsValidA(x, y) != 1)
        return;
    if (PillDir & 1)
        MapA[(x << 6) + y] = PillarMap[(x % 6) << 1];
    else
        MapA[(x << 6) + y] = PillarMap[(y % 6) << 1];
}
