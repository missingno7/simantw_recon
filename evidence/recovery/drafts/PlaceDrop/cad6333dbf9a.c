extern unsigned char near MapA[128][64];
extern unsigned char far Dx8[];
extern unsigned char far RxTab[];
extern unsigned char far RyTab[];
extern int far RRand(int range);
void far PlaceDrop(int i)
{
 int x,y,mapIndex,scentIndex;
 x=RRand(128); y=RRand(64); RxTab[i]=x; RyTab[i]=y;
 mapIndex=(x<<6)+y;
 if (MapA[0][mapIndex] < 0xe) {
  MapA[0][mapIndex]=0x74;
  scentIndex=((x/2)*32)+(y/2);
  Dx8[scentIndex+0x52d2]=0; Dx8[scentIndex+0x5ad2]=0;
  if (Dx8[scentIndex+0x62d2]>=0x14) Dx8[scentIndex+0x62d2]-=0x14;
  else Dx8[scentIndex+0x62d2]=0;
  Dx8[scentIndex+0x6ad2]=0;
  if (Dx8[scentIndex+0x72d2]>=0x14) Dx8[scentIndex+0x72d2]-=0x14;
  else Dx8[scentIndex+0x72d2]=0;
  Dx8[scentIndex+0x7ad2]=0;
 }
}