/* Candidate translation unit simant1_9612_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _GetSmellT
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern unsigned char far Dy8[];
extern unsigned char far Dx8[];
#define PherMapRT ((unsigned char far *)((unsigned char far *)PherMapBT + 0x1000))  /* pool word C476: one object, MAPSYM _PherMapBT+4096 */
extern unsigned char far PherMapBT[];




int near GetSmellT(int x, int y, int index, int red)
{
  int value;
  int mapX;
  int mapY;
  mapY = ((signed char) Dy8[index]) + y;
  mapX = ((signed char) Dx8[index]) + x;
  if (mapX < 0)
    return 0;
  if (mapX > 0x3f)
    return 0;
  if (mapY < 0)
    return 0;
  if (mapY > 0x1f)
    return 0;
  if (red)
    return PherMapRT[(mapX << 5) + mapY];
  value = mapX << 5;
  return PherMapBT[value + mapY];
}

