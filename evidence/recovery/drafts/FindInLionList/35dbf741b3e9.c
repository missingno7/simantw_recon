extern unsigned int far LionListState[];
extern unsigned char far match_position[];
extern unsigned char far match_position_es[];

int FindInLionList(int firstKey, int secondKey) {
 int index = LionListState[0x4544] - 1;
 if (index < 0) return index;
 for (; index >= 0; --index) {
  if (match_position[index - 0x7f64] == firstKey &&
      match_position_es[index - 0x7f44] == secondKey) return index;
 }
 return index;
}
