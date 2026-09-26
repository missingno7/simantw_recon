/* Read the R ant record, reverse its direction, apply the corresponding signed deltas, and add its new tail with the tail marker. */
extern unsigned char far RlistT[];
extern unsigned char far RlistX[];
extern unsigned char far RlistY[];
extern signed char far Dx8[];
extern signed char far Dy8[];
extern void far AddAntToRList(int life, int column, int attribute, int state, int direction);

void far MakeNewTailR(int index)
{
    unsigned char type;
    unsigned char direction;
    int life;
    int column;

    type = RlistT[index];
    direction = type;
    direction &= 7;
    direction ^= 4;
    column = RlistY[index] + (signed char)Dy8[direction + 8];
    life = RlistX[index] + (signed char)Dx8[direction];
    AddAntToRList(life, column, type + 8, 9, 0);
}
