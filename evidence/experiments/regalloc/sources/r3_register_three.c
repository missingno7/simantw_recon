extern void far Touch(int);
int far RallocFindMem(int a0,int b0,int c0,int n){ register int a=a0; register int b=b0; register int c=c0; int i; for(i=0;i<n;i++){ Touch(a); Touch(b); Touch(c); a+=b0; b+=c0; c+=a0; } return a+b+c+i; }
