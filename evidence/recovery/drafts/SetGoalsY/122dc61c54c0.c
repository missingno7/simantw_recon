/* Test parameter register homes while preserving the best known branch structure. */
extern int far MeGoalPlane; extern int far MeGoalX; extern int far MeGoalY; extern int far MeCrazyCnt;
void far SetGoalsY(int plane, int x, int y) {
 register int p; p=plane; if(p==0) MeGoalPlane=1; else MeGoalPlane=p;
 MeGoalX=x; MeGoalY=y; MeCrazyCnt=-2;
 if(plane>=2 && y<2){ if(x<=0){ x=1; } else if(x>=0x3f){ x=0x3e; MeGoalX=x; } }
}
