/* Hypothesis: use the same-object far helper declaration so LINK can lower its call as it does in the admitted unit */
struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far RlistX;
extern signed char far Dy8[];
extern signed char far Dx8[];
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int far Tindex;




extern int far GetOutR(int x);

/* Keep the signed direction guard; a negative direction exits, while zero and positive directions read the red displacement tables. The target reaches its local GetOutR path with a direct same-segment near call. */
int far TryMoveDirR(int x, int y, int dir)
{
  unsigned offset;
  int dy;
  int dx;
  if (dir < 0)
    return 0;
  dx = Dx8[dir] + x;
  dy = Dy8[dir] + y;
  if (dx > 0x3f)
    return 0;
  if (dx < 0)
    return 0;
  if (dy > 0x3f)
    return 0;
  if (dy < 1)
    return GetOutR(x);
  if (MapR[dx * 64 + dy] >= 0x1c)
    return 0;
  LifeR[dx * 64 + dy] = RlistX.t[Tindex] & 0xf8 | dir;
  LifeR[x * 64 + y] = 0;
  offset = dx * 64;
  RlistX.x[Tindex] = LifeR[offset + dy];
  RlistX.y[Tindex] = (unsigned char) dy;
  RlistX.t[Tindex] = LifeR[dx * 64 + dy];
  return 1;
}




