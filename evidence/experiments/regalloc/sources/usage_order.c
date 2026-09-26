int far RallocFindMem(int p, int q, int r) {
 int a=p, b=q, c=r, d=p+1;
 int i;
 for(i=0;i<6;i++){ a+=b; a+=b; c+=d; c+=d; d+=i; }
 return a+b+c+d+i;
}
