/* direct_x/seq/named */
struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far RlistX;
extern signed char far Dx8[];extern signed char far Dy8[];extern void far AddAntToRList(int,int,int,int,int);void far MakeNewTailR(int index){
    unsigned char type;
    unsigned char direction;
    int life;
    int column;

    type = RlistX.t[index];
    direction = type;
    direction &= 7;
    direction ^= 4;
    life = RlistX.x[index] + (signed char)Dx8[direction];
    column = RlistX.y[index] + (signed char)Dy8[direction];
    AddAntToRList(life, column, type + 8, 9, 0);
}
