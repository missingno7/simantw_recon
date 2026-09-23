extern int far IsValidA(int x, int y);
extern unsigned char near MapA[128][64];
void PlacePillTile(int x,int y,unsigned char value) { int column=x, row=y; if (IsValidA(column,row) == 1) MapA[column][row] = value; }