extern int far GlobalA; extern int far GlobalB; extern void far Probe(void);
int far SimQueenR(int p){ int x,y; x=GlobalA+GlobalB; Probe(); y=GlobalA+GlobalB; return x+y+p; }
