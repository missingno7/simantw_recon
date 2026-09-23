extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];
void PlacePillTile(int x,int y,unsigned char value) { int row=y, column=x; if (IsValidA(column,row) == 1) MapA[row + column*64] = value; }