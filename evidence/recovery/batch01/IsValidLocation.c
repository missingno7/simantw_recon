/* Recovery candidate: modern filename; historical source unavailable. */
int IsValidLocation(int level,int x,int y) { if(level<=1) return x>=0 && x<=127 && y>=0 && y<=63; else return x>=0 && x<=63 && y>=0 && y<=63; }
