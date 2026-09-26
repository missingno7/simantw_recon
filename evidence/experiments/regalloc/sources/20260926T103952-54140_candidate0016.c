int far RallocFindMem(int p, int q, int r) {
 register int b=q; register int a=p; int c=r, d=p+1, i;
 for(i=0;i<6;i++){ a+=b; a+=b; c+=d; c+=d; d+=i; }
 return a+b+c+d+i;
}
