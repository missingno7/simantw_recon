extern void far Touch(int);
int far RallocFindMem(register int p,int q,int n){ int i; for(i=0;i<n;i++){ Touch(p); p+=q; } return p+i; }
