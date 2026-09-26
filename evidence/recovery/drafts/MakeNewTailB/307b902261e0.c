/* Read the B ant record, reverse its direction, apply the corresponding signed deltas, and add its new tail with the tail marker. */
extern unsigned char far BlistT[];
extern unsigned char far BlistX[];
extern unsigned char far BlistY[];
extern signed char far Dx8[];
extern signed char far Dy8[];
extern void far AddAntToBList(int life, int column, int attribute, int state, int direction);

void far MakeNewTailB(int index)
{
    unsigned char type;
    unsigned char direction;
    int life;
    int column;

    type = BlistT[index];
    direction = type;
    direction &= 7;
    direction ^= 4;
    column = BlistY[index] + (signed char)Dy8[direction + 8];
    life = BlistX[index] + (signed char)Dx8[direction];
    AddAntToBList(life, column, type + 8, 9, 0);
}
