/*
 * Hypothesis: the B-tail record at index supplies its type, column and life.
 * The low three type bits select one of eight directions, with the B-side
 * table's fourth bit toggled before indexing Dx8/Dy8.  The new tail is eight
 * type units above the old type, its column is shifted by Dy8[index+8], its
 * life by Dx8[index], and the verified B-list insertion receives state 9 and
 * direction 0.
 */
extern unsigned char far BlistT[];
extern unsigned char far BlistY[];
extern signed char far Dx8[];
extern signed char far Dy8[];
extern void far AddAntToBList(int life, int column, int attribute,
                              int state, int direction);

void far MakeNewTailB(int index)
{
    int type;
    int direction;
    int life;
    int column;

    type = BlistT[index + 0x3d18];
    direction = (type & 7) ^ 4;
    life = BlistT[index + 0x3736] + Dx8[direction];
    column = BlistY[index + 0x392c] + Dy8[direction + 8];
    AddAntToBList(life, column, type + 8, 9, 0);
}
