/*
 * Hypothesis: validate a tile coordinate, accept an already saturated MapA
 * tile when TERRAINset is active, otherwise require IsClear3x3 before
 * creating the new hole.  The two helpers are near calls in SIMONE_MODULE;
 * TERRAINset is far data and MapA is the observed DGROUP byte grid.
 */
extern int far TERRAINset;
extern unsigned char near MapA[];
extern int far IsClear3x3(int x, int y, int mode);
extern void far CreateNewHole(int x, int y);

int far DigMyNewHole(int x, int y)
{
    if (x < 1 || x > 0x7f || y < 1 || y > 0x3f)
        return 0;

    if (TERRAINset && MapA[(x << 6) + y] >= 0xc8)
        return 1;

    if (IsClear3x3(x, y, 1) != 1)
        return 0;
    CreateNewHole(x, y);
    return 1;
}
