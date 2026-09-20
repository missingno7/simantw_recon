/*
 * An ant-lion record stores its x and y map coordinates and a tile-kind
 * byte.  SetAntLion publishes the corresponding occupied tile through
 * SetMap on plane 1, adding the ant-lion tile bias 0x38 to the kind.
 */
extern unsigned char far antLionX[];
extern unsigned char far antLionY[];
extern unsigned char far antLionType[];
extern void far SetMap(int plane, int x, int y, int value);

void SetAntLion(int index)
{
    SetMap(1, antLionX[index], antLionY[index], antLionType[index] + 0x38);
}
