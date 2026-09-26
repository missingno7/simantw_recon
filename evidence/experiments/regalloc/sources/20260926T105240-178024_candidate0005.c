extern void far Probe(void);
int far SimQueenR(int p,int q,int r,int s){ int a=p+q; int b=p+r; int c=q+s; int d=r+s; Probe(); return (p+q)+(p+r)+(q+s)+(r+s); }
