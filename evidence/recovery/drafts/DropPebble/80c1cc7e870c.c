/*
 * DropPebble hypothesis revision 3. It follows the CFG's separate surface
 * call, bounds/tile-0x18 branch, reciprocal underground-hole update, later
 * hole/entrance branch, and final bounded write. The verified GetMap and
 * IsLiftable sources support the map dimensions and switch shape. HoleMapB/R
 * are the named far segment-8 arrays; their target selector words are C4A8
 * and C4AA.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern unsigned char far HoleMapB[];
extern unsigned char far HoleMapR[];
extern int far IsItHole(int x, int y);
extern void far ZapEuMapAt(int plane, int x, int y);

void far DropPebble(int plane, int x, int y)
{
  int ok;
  int value;
  int row;
  register int rx;
  if (plane > 1)
    goto stage_two;
  if (plane > 1)
    goto non_surface_entry;
  rx = x;
  ok = IsItHole(rx, y);
  goto first_gate;
  non_surface_entry:
  if (y > 0)
  {
    ok = 0;
  }
  else
  {
    ok = 0;
    if (plane <= 1)
      ok = x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f;
    else
      ok = x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f;
    if (ok != 1)
    {
      ok = 0;
    }
    else
    {
      ok = 0;
      switch (plane)
      {
        case 0:

        case 1:
          ok = MapA[x][y] == 0x18;
          break;

        case 2:
          ok = MapB[x][y] == 0x18;
          break;

        case 3:
          ok = MapR[x][y] == 0x18;
          break;

      }

    }
  }

  first_gate:
  if (ok)
  {
    if (rx >= 0x40)
    {
      if (HoleMapR[y] == rx)
      {
        MapR[rx][y] = 0x31;
        value = 0x51;
        goto finish;
      }
    }
    else
    {
      if (HoleMapB[y] != rx)
      {
        if (HoleMapR[y] == rx)
        {
          (*(MapR + rx))[y] = 0x31;
          value = 0x51;
          goto finish;
        }
      }
      else
      {
        MapB[rx][y] = 0x31;
        value = 0x51;
        goto finish;
      }
    }
  }

  stage_two:
  if (plane <= 1)
  {
    rx = x;
    ok = IsItHole(rx, y);
  }
  else
    if (y > 0)
  {
    ok = 0;
  }
  else
  {
    ok = 0;
    if (plane <= 1)
      ok = x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f;
    else
      ok = x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f;
    if (ok == 1)
    {
      ok = 0;
      switch (plane)
      {
        case 2:
          ok = MapB[x][y] == 0x18;
          break;

        case 3:
          ok = MapR[x][y] == 0x18;
          break;

      }

    }
    else
    {
      ok = 0;
    }
  }

  if (ok != 0)
  {
    if (plane == 2)
      row = HoleMapB[x];
    else
      row = HoleMapR[x];
    MapA[x][row] = 0x51;
    value = 0x31;
    goto finish;
  }
  value = 0x30;
  finish:
  if (plane <= 1)
    ok = x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f;
  else
    ok = (!((!(x >= 0 && x <= 0x3f)) || y < 0)) && y <= 0x3f;

  if (ok != 0)
  {
    switch (plane)
    {
      case 0:

      case 1:
        MapA[x][y] = value;
        break;

      case 2:
        MapB[x][y] = value;
        break;

      case 3:
        MapR[x][y] = value;
        break;

    }

    ZapEuMapAt(plane, x, y);
  }
}

