int far RallocFindMem(int p, int q, int r) {
 int a=p, b=q, c=r, d=p+1;
 int i;
 for(i=0;i<6;i++){ d+=i; c+=d; c+=d; b+=a; a+=b; }
 return a+b+c+d+i;
}
