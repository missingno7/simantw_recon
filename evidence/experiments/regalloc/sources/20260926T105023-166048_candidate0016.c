extern void far Touch(int);
int far RallocFindMem(int a0,int b0,int c0,int n){ int hot=a0,mid=b0,cold=c0,i; for(i=0;i<n;i++){ Touch(cold); Touch(cold); Touch(cold); Touch(mid); Touch(hot); hot+=b0; mid+=c0; cold+=a0; } return hot+mid+cold+i; }
