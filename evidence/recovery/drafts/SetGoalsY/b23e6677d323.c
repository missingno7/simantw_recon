/* Set the yellow ant's goal coordinates, limiting its early search plane. */
extern int far MeGoalPlane; extern int far MeGoalX; extern int far MeGoalY; extern int far MeCrazyCnt;
void far SetGoalsY(int plane,int x,int y){ if(plane==0) plane=1; MeGoalPlane=plane; MeGoalX=x; MeGoalY=y; MeCrazyCnt=-2; if(plane>=2 && y<2){ if(x<=0) x=1; else if(x>=63) x=62; MeGoalX=x; } }
