/* Compare each lion's two match-position bytes while scanning backward. */
extern int far LionIndex;
extern unsigned char far LionListX[];
extern unsigned char far LionListY[];

int FindInLionList(int firstKey, int secondKey) {
 int index = LionIndex - 1;
 if (index < 0) return index;
 while (index >= 0) {
  if (LionListX[index] == firstKey) {
   if (LionListY[index] == secondKey) break;
  }
  --index;
 }
 return index;
}
