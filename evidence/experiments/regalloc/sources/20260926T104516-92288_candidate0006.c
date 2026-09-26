extern void far Touch(int);
int far RallocFindMem(int a0,int b0,int c0){ register int x=a0+1; register int y=b0+2; Touch(c0); Touch(c0+1); return x+y+c0; }
