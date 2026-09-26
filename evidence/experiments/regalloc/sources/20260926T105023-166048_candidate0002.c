extern void far Touch(int);
int far RallocFindMem(int a0,int b0,int c0,int n){ int i; for(i=0;i<n;i++){ Touch(a0); Touch(a0); Touch(a0); Touch(b0); Touch(c0); a0+=b0; b0+=c0; c0+=a0; } return a0+b0+c0+i; }
