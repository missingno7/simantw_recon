/* Recovery candidate: modern filename; historical source unavailable. */
extern int SRand1(int);
int SGRand(int n) { int a,b; a=SRand1(n); b=SRand1(n); return a<b?a:b; }
