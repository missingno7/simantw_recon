/*
 * DigTileThemB(x, y): AI-nest digging helper for the black colony. Returns 0
 * without digging when the target cell is out of the diggable interior band
 * (x == 0 or x > 62), or when an in-bounds vertical neighbour in the same
 * column (y - 1 / y + 1, checked only when in range) is not a dirt tile per
 * IsItDirt. Otherwise it carves the cell: row y == 0 seeds the nest-entrance
 * marker 0x18 into MapB and opens a new surface hole via MakeNewHoleB(x);
 * any other row gets a random dirt-tile byte from SRand8(). The dig totals
 * TileTotXB/TileTotYB accumulate x/y, TilesDugB is pre-incremented, and while
 * the resulting count is positive the running averages TileMassXB/TileMassYB
 * are recomputed as TileTotXB/TileTotYB divided by that count (32-bit
 * division via the runtime long divide). The four orthogonal neighbours are
 * re-smoothed with SmoothEdgesB and the exit-flow map is refreshed with
 * FixExitMapB before returning 1 for a successful dig. Twin of DigTileThemR;
 * MapB/TilesDugB/TileTotXB/TileTotYB/TileMassXB/TileMassYB/MakeNewHoleB and
 * the (x, y) parameter order are reused verbatim from the admitted
 * FillDirtB and the RandWorld/DigOutBNest translation unit
 * (src/recovered/wf_FillDirtB-b73109489f.c,
 * src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c), and the dirt
 * band test from the admitted IsItDirt (src/recovered/wf_IsItDirt-30ab0b6cc4.c).
 */
extern unsigned char near MapB[64][64];
extern int far TilesDugB;
extern long far TileTotXB;
extern long far TileTotYB;
extern int far TileMassXB;
extern int far TileMassYB;

extern int far IsItDirt(int value);
extern void far MakeNewHoleB(int x);
extern int far SRand8(void);
extern void far SmoothEdgesB(int x, int y);
extern void far FixExitMapB(int x, int y);

int far DigTileThemB(int x, int y)
{
  volatile int cntHome;
  int perm_x_2;
  perm_x_2 = x;
  if (y < 0x3f)
  {
    if (!IsItDirt(MapB[perm_x_2][y + 1]))
      goto bad;
  }
  if (y > 2)
  {
    if (!IsItDirt(MapB[perm_x_2][y - 1]))
      goto bad;
  }
  if (perm_x_2 == 0)
    goto bad;
  if (perm_x_2 > 0x3e)
    goto bad;
  if (y == 0)
  {
    *((*(MapB + perm_x_2)) + y) = 0x18;
    MakeNewHoleB(perm_x_2);
  }
  else
  {
    MapB[perm_x_2][y] = (unsigned char) SRand8();
  }
  TileTotXB += perm_x_2;
  TileTotYB += y;
  cntHome = ++TilesDugB;
  if (TilesDugB > 0)
  {
    TileMassXB = TileTotXB / TilesDugB;
    TileMassYB = TileTotYB / TilesDugB;
  }
  SmoothEdgesB(perm_x_2, y - 1);
  SmoothEdgesB(perm_x_2 + 1, y);
  SmoothEdgesB(perm_x_2, y + 1);
  SmoothEdgesB(perm_x_2 - 1, y);
  FixExitMapB(perm_x_2, y);
  return 1;
  bad:
  return 0;

}

