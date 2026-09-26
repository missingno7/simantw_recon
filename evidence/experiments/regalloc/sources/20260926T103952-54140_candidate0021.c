int far RallocFindMem(int p, int q, int r) {
 volatile int a=p; int b=q, c=r, i;
 for(i=0;i<4;i++){ a+=b; c+=a; }
 return a+b+c+i;
}
