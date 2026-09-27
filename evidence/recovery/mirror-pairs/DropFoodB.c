/* Derived mechanically from the mirrored colony function _DropFoodR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped DropFoodR->DropFoodB, FoodR->FoodB, MapR->MapB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/* volatile/classic */
extern unsigned char near MapB[];extern int far FoodB;extern int far Tindex;extern unsigned char far Dx8[];int far DropFoodB(int x,int y){volatile unsigned char near *cell; int level; int result; unsigned char far *attrPtr;cell=&MapB[(x<<6)+y];result=0;level=*cell;if(level<16){*cell=16;result=1;}else if(level<19){(*cell)++;result=1;}FoodB++;attrPtr=&Dx8[Tindex+0x3D18];if(*attrPtr&8)*attrPtr-=8;return result;}
