extern void far Touch(int);
int far RallocFindMem(int a0,int b0,int c0,int n){ register int hot=a0; register int mid=b0; int cold=c0,i; for(i=0;i<n;i++){ Touch(hot); Touch(hot); Touch(hot); Touch(mid); Touch(cold); hot+=b0; mid+=c0; cold+=a0; } return hot+mid+cold+i; }
