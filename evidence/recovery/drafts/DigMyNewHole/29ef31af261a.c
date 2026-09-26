/* Use sequential coordinate guards and a common success return after the helper call. */
extern int far TERRAINset; extern unsigned char near MapA[];
extern int far IsClear3x3(int plane,int x,int y); extern void far CreateNewHole(int x,int y);
int far DigMyNewHole(int x,int y){ register int result; result=0; if(x>=1){ if(x<=0x7f){ if(y>=1){ if(y<=0x3f){ if(TERRAINset!=0){ if(MapA[(x<<6)+y]<0xc8) result=1; CreateNewHole(x,y); result=1; } else { result=IsClear3x3(1,x,y); if(result==1) CreateNewHole(x,y); } } } } } return result; }
