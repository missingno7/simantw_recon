extern int far match_position[];
extern unsigned char far Dx8[];
extern unsigned char near LifeA[];

void far AddAntToAList(int life, int column, int attribute,
                       int state, int direction)
{
    int index;

    index = match_position[0x4078];
    if (index >= 1000)
        return;
    Dx8[index + 0x23a4] = (unsigned char)life;
    Dx8[index + 0x278e] = (unsigned char)column;
    Dx8[index + 0x2b78] = (unsigned char)state;
    Dx8[index + 0x2f62] = (unsigned char)attribute;
    Dx8[index + 0x334c] = (unsigned char)direction;
    LifeA[(index << 6) + column] = (unsigned char)attribute;
    ++match_position[0x4078];
}
