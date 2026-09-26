extern int far Probe(int);
int far SimQueenR(int p, int q, int r) {
 register int keep=p+q; int a=Probe(r); int b=Probe(a+1);
 return keep+a+b;
}
