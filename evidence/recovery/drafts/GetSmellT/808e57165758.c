/*
 * Hypothesis: adjust the two requested coordinates by the indexed Dy8/Dx8
 * scent offsets, reject coordinates outside the 64 by 32 map, and read the
 * selected red-team or blue-team pheromone byte.  The lookup arrays follow
 * the verified JamScent family and are unsigned so the final byte is zero
 * extended as in the target.
 */
extern unsigned char far Dy8[];
extern unsigned char far Dx8[];
extern unsigned char far PherMapRT[];
extern unsigned char far PherMapBT[];

int near GetSmellT(int x, int y, int index, int red)
{
    int mapX;
    int mapY;

    mapY = (signed char)Dy8[index + 8] + y;
    mapX = (signed char)Dx8[index] + x;
    if (mapX < 0) return 0;
    if (mapX > 0x3f) return 0;
    if (mapY < 0) return 0;
    if (mapY > 0x1f) return 0;

    if (red)
        return PherMapRT[(mapX << 5) + mapY];
    return PherMapBT[(mapX << 5) + mapY];
}
