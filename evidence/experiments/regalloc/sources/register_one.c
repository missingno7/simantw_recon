int far RallocFindMem(int p, int q, int r) {
 int c=r, d=p+1; register int best=p; int i;
 for(i=0;i<6;i++){ best+=q; c+=d; d+=i; }
 return best+c+d+i;
}
