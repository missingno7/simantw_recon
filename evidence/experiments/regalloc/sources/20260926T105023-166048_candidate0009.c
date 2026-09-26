extern void far Touch(int);
int far RallocFindMem(int far *input,int v){ int far * volatile p=input; int a=*p; Touch(v); return *p+a; }
