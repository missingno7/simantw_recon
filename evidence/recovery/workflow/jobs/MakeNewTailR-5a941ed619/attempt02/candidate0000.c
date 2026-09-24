/* Source-backed mirror hypothesis with explicit temporaries, using the current packet's R-side offsets. */
extern unsigned char far RlistT[];
extern unsigned char far RlistY[];
extern signed char far Dx8[];
extern signed char far Dy8[];
extern void far AddAntToRList(int life, int column, int attribute,
                              int state, int direction);

void far MakeNewTailR(int index)
{
    int type;
    int direction;
    int life;
    int column;

    type = RlistT[index + 0x46e6];
    direction = (type & 7) ^ 4;
    life = RlistT[index + 0x4104] + Dx8[direction];
    column = RlistY[index + 0x42fa] + Dy8[direction + 8];
    AddAntToRList(life, column, type + 8, 9, 0);
}
