extern void far Touch(int);
int far RallocFindMem(int a0,int b0,int c0,int n){ int cold=c0,mid=b0,hot=a0,i; for(i=0;i<n;i++){ Touch(hot); Touch(hot); Touch(hot); Touch(mid); Touch(cold); hot+=b0; mid+=c0; cold+=a0; } return hot+mid+cold+i; }
