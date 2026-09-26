extern void far Touch(int);
int far RallocFindMem(int a0,int b0,int n){ register int a=a0; register int b=b0; int i; for(i=0;i<n;i++){ Touch(a); Touch(b); a+=b0; b+=a0; } return a+b+i; }
