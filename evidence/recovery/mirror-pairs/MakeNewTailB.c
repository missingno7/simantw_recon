/* Derived mechanically from the mirrored colony function _MakeNewTailR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped AddAntToRList->AddAntToBList, MakeNewTailR->MakeNewTailB, RlistX->BlistX; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/* direct_x/seq/named */
struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far BlistX;
extern signed char far Dx8[];extern signed char far Dy8[];extern void far AddAntToBList(int,int,int,int,int);void far MakeNewTailB(int index){
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
