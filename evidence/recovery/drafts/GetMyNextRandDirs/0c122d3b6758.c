extern char far Dx8[]; extern char far Dy8[]; extern int far MeCrazyCnt; extern int far match_position[];
extern int far GetMyBestDirs(int plane,int x,int y,int a,int b);
extern void far GetMyRandDirs(int far *outDirA,int far *outDirB,int plane,int x,int y,int a,int b);
int far GetMyNextRandDirs(int plane,int x,int y,int a,int b)
{
 int dir; int nx; int ny; int tries;
 tries=0;
 dir=GetMyBestDirs(plane,x,y,a,b);
 if(dir>=0){
  nx=x+Dx8[dir]; ny=y+Dy8[dir];
  while(dir>=0 && tries<0x40){
   dir=GetMyBestDirs(plane,nx,ny,a,b);
   if(dir>=0){nx+=Dx8[dir]; ny+=Dy8[dir];}
   tries++;
  }
  if(dir>=0) dir=-1;
 }
 if(dir==-2){GetMyRandDirs((int far *)&match_position[0x78a4/2],(int far *)&match_position[0xa0d8/2],plane,x,y,a,b);} else {MeCrazyCnt=-1; return GetMyBestDirs(plane,x,y,a,b);}
}
