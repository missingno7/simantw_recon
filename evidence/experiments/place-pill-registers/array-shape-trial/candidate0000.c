extern int far IsValidA(int x, int y);
extern unsigned char near MapA[128][64];
void PlacePillTile(int x,int y,unsigned char value) { if (IsValidA(x,y) == 1) MapA[x][y] = value; }