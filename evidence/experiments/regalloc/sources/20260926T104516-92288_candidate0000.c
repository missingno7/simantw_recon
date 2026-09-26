extern void far Touch(int); extern void far TouchPtr(int near *);
int far RallocFindMem(int a0,int b0,int c0,int n){ int hot=a0,mid=b0,cold=c0,i; TouchPtr(&hot); for(i=0;i<n;i++){ Touch(hot); Touch(hot); Touch(mid); Touch(cold); hot+=b0; mid+=c0; cold+=a0; } return hot+mid+cold+i; }
