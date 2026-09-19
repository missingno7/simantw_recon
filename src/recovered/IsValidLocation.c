int IsValidLocation(int level,int x,int y) { int valid; if(level<=1) valid=x>=0 && x<=127 && y>=0 && y<=63; else valid=x>=0 && x<=63 && y>=0 && y<=63; return valid; }
