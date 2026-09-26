extern int far ListIndexA[];
extern unsigned char far Dx8[];
extern void near RemoveFromAList(int index);
int GetFromAlist(int wanted) { int index; int type; index=ListIndexA[0]; while (index > 0) { --index; type=Dx8[index+0x2f62]; if (type != 0 && (type >> 7) == wanted) { if (index > 0) { RemoveFromAList(index); return 1; } return 0; } } return 0; }
