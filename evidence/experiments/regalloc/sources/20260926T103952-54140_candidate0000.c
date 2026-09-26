extern void near Observe(int near *);
int far RallocFindMem(int p, int q, int r) {
 int a=p, b=q, c=r;
 Observe(&a);
 for(c=0;c<3;c++) a+=b;
 return a+c;
}
