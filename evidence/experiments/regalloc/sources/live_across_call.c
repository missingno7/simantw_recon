extern int far Probe(int);
int far RallocFindMem(int p, int q, int r) {
 int keep=p+q, other=r+1;
 other=Probe(other);
 return keep+other;
}
