/* Derived mechanically from the mirrored colony function _MakeNewTailR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped AddAntToRList->AddAntToBList, MakeNewTailR->MakeNewTailB, RlistT->BlistT, RlistX->BlistX, RlistY->BlistY; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/* direct_x/seq/named */
extern unsigned char far BlistT[];extern unsigned char far BlistX[];extern unsigned char far BlistY[];extern signed char far Dx8[];extern signed char far Dy8[];extern void far AddAntToBList(int,int,int,int,int);void far MakeNewTailB(int index){unsigned char type; unsigned char direction; int life; int column;life=BlistX[index]+(signed char)Dx8[direction]; type=BlistT[index];direction=(unsigned char)type;direction &= 7;direction ^= 4;AddAntToBList(life,BlistY[index]+(signed char)Dy8[direction],type+8,9,0);}
