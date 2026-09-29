/* Read the selected life plane and its compact list before asking FindLifeIndex for the matching egg record. */
extern int far FindLifeIndex(int list, int life, int column, int low, int high, int mask);
extern int far GetAntIndex(int list, int index, int far *life, int far *column, int far *attribute, int far *state, int far *direction);
extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char near LifeA[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern unsigned char far Dx8;

int far FindEggAt(int far *outIndex, volatile int which, int life, int column)
{
  volatile int index;
  int tag;
  unsigned char far * volatile lifeList;
  unsigned char far * volatile columnList;
  unsigned char far * volatile attributeList;
  int rawTile;
  int tile;
  int outLife;
  int valid;
  int direction;
  int state;
  int attribute;
  int eggColumn;
  index = -1;
  if (which <= 1)
    valid = life >= 0 && life <= 0x7f && column >= 0 && column <= 0x3f;
  else
    valid = life >= 0 && life <= 0x3f && column >= 0 && column <= 0x3f;
  if ((--valid) != 0)
  {
    rawTile = index;
  }
  else
  {
    switch (which)
    {
      case 0:

      case 1:
        rawTile = LifeA[(life << 6) + column];
        break;

      case 2:
        rawTile = LifeB[(life << 6) + column];
        break;

      case 3:
        rawTile = LifeR[(life << 6) + column];
        break;

      default:
        rawTile = index;
        break;

    }

  }
  outLife = rawTile;
  if (outLife == 0)
    goto fail;
  tag = outLife;
  tag &= 0x7f;
  if (tag < 1 || tag > 7)
    goto fail;
  if (outLife == 0xff || outLife == 0xfe)
    goto fail;
  tile = outLife;
  if (which <= 0)
    goto fail;
  if (which == 1)
  {
    index = ListIndexA;
    lifeList = (&Dx8) + 0x23a4;
    columnList = (&Dx8) + 0x278e;
    attributeList = (&Dx8) + 0x2f62;
  }
  else
    if (which == 2)
  {
    index = ListIndexB;
    lifeList = (&Dx8) + 0x3736;
    columnList = (&Dx8) + 0x392c;
    attributeList = (&Dx8) + 0x3d18;
  }
  else
    if (which == 3)
  {
    index = ListIndexR;
    lifeList = (&Dx8) + 0x4104;
    columnList = (&Dx8) + 0x42fa;
    attributeList = (&Dx8) + 0x46e6;
  }
  else
    goto fail;
  --index;
  while (index >= 0 && (lifeList[index] != life || columnList[index] != column || attributeList[index] != tile))
    --index;

  if ((index = FindLifeIndex(which, life, column, 1, 7, 0x7f)) < 0)
    goto fail;
  GetAntIndex(which, index, &outLife, &eggColumn, &attribute, &state, &direction);
  *outIndex = index;
  return outLife;
  fail:
  index = -1;

  *outIndex = index;
  return index;
}

