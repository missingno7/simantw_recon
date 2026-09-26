extern void far Touch(int);
int far RallocFindMem(int a0,int b0,int c0,int n){ signed char hot=(signed char)a0; int mid=b0,cold=c0,i; for(i=0;i<n;i++){ Touch(hot); Touch(hot); Touch(mid); Touch(cold); hot=(signed char)(hot+1); mid+=c0; cold+=a0; } return hot+mid+cold+i; }
