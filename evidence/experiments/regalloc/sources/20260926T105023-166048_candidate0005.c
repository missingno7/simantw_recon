extern void far Touch(int);
int far RallocFindMem(int a0,int b0,int c0){ register int x=a0+1; int y=b0+2; Touch(c0); return x+y+c0; }
