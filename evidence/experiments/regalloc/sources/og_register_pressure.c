extern void far Probe(void);
int far SimQueenR(int p,int q,int r,int s){ register int a=p+q; register int b=p+r; register int c=q+s; register int d=r+s; Probe(); return a+b+c+d; }
