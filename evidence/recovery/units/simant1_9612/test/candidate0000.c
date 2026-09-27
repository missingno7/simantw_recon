/* Candidate translation unit simant1_9612: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _GetSmellT */

extern unsigned char far Dy8[];
extern unsigned char far Dx8[];
extern unsigned char far PherMapRT[];
extern unsigned char far PherMapBT[];

int near GetSmellT(int x, int y, int index, int red)
{
  int value;
  int mapX;
  int mapY;
  mapY = ((signed char) Dy8[index + 8]) + y;
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

