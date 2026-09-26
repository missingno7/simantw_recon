extern int far GlobalA; extern int far GlobalB; extern int far GlobalC; extern int far GlobalD; extern void far Probe(void);
int far SimQueenR(int p){ int a,b,c,d; a=GlobalA+GlobalB; b=GlobalB+GlobalC; c=GlobalC+GlobalD; d=GlobalD+GlobalA; Probe(); return a+b+c+d+p; }
