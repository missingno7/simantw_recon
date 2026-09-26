extern void far Touch(int);
int far RallocFindMem(int p,int q,int n){ int value=p; int i; for(i=0;i<n;i++){ Touch(value); value+=q; } return value+i; }
