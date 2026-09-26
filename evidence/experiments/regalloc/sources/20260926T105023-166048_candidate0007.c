extern void far Touch(int);
int far RallocFindMem(int a0,int b0,int n){ int looped=a0, once=b0,i; for(i=0;i<n;i++){ Touch(looped); Touch(looped); looped+=a0; } Touch(once); return looped+once+i; }
