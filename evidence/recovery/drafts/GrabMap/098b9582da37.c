/* row temporary shifted before reusing direct y parameter; tests local lifetime/reuse and early-return tails. */
extern unsigned char near MapA[];
int GrabMap(int x, int y) {
  int index;
  int perm_y_2;
  int pos;
  register int perm_x_2;
  if ((perm_x_2 = x) > 0x7f)
  {
    index = 0;
  }
  else
  {
    if (perm_x_2 < 0)
      index = 0x7f;
    else
      index = perm_x_2;
  }
  perm_y_2 = y;
  if (perm_y_2 > 0x3f)
  {
    perm_y_2 = 0;
  }
  else
  {
    if (perm_y_2 < 0)
      perm_y_2 = 0x3f;
  }
  index <<= 6;
  pos = index + perm_y_2;
  return *(MapA + pos);
}

