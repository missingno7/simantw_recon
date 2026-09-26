int far RallocFindMem(int p, int q, int r) {
 int i;
 for(i=0;i<6;i++){ p+=q; r+=p; q+=i; }
 return p+q+r+i;
}
