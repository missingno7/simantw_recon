extern void far TouchPtr(int near *);
int far RallocFindMem(int p){ int outer[4]; int x[2]; int y[2]; int i; for(i=0;i<2;i++){ x[0]=p+i; x[1]=p-i; y[0]=p+i+1; y[1]=p-i-1; TouchPtr(x); TouchPtr(y); outer[i]=x[0]+y[0]; } return outer[0]+outer[1]+i; }
