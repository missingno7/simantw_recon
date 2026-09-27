/* B-side mirror of the admitted MakeNewTailR body. */
struct BListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct BListPlanes far BlistX;
extern signed char far Dx8[];
extern signed char far Dy8[];
extern void far AddAntToBList(int, int, int, int, int);

void far MakeNewTailB(int index)
{
    unsigned char type;
    int direction;
    int life;
    int column;

    type = BlistX.t[index];
    direction = type & 7;
    direction ^= 4;
    life = BlistX.x[index] + (signed char)Dx8[direction];
    column = BlistX.y[index] + (signed char)Dy8[direction];
    AddAntToBList(life, column, type + 8, 9, 0);
}
