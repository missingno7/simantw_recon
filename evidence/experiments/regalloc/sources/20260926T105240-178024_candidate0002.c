extern int far GlobalA; extern void far Probe(void);
int far SimQueenR(int p) {
 int x=GlobalA; Probe(); return x+GlobalA+p;
}
