/* Compare each lion's two match-position bytes while scanning backward. */
extern int far LionIndex;
extern unsigned char far match_position[];

int FindInLionList(int firstKey, int secondKey) {
 int index = LionIndex - 1;
 if (index < 0) return index;
 while (index >= 0) {
  if (match_position[index - 0x7f64] == firstKey) {
   if (match_position[index - 0x7f44] == secondKey) break;
  }
  --index;
 }
 return index;
}
