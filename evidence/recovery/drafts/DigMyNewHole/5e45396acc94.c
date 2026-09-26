/* Keep the validated coordinate guard and retain the result in a register local. */
extern int far TERRAINset; extern unsigned char near MapA[];
extern int far IsClear3x3(int plane,int x,int y); extern void far CreateNewHole(int x,int y);
int far DigMyNewHole(int x,int y){ register int result; result=0; if(x>=1 && x<=0x7f && y>=1 && y<=0x3f){ if(TERRAINset && MapA[(x<<6)+y]>=0xc8) result=1; else { result=IsClear3x3(1,x,y); if(result==1){ CreateNewHole(x,y); result=1; } else result=0; } } return result; }
