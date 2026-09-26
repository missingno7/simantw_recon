extern int far Probe(int);
int far RallocFindMem(int p, int q, int r) {
 register int keep=p+q; register int other=r+1;
 other=Probe(other);
 return keep+other;
}
