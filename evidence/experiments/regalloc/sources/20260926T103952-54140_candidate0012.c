int far RallocFindMem(int p, int q, int r) {
 int a=p, b=q, c=r, i;
 for(i=0;i<6;i++){ a+=b; c+=a; b+=r; }
 return a+b+c+i;
}
