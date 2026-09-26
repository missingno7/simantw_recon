static unsigned int seed;
extern unsigned long far TickCount(void);
extern int far SRand128(void);
extern void far srand(unsigned int value);
extern int far rand(void);

int RRand(int limit) { int v=rand(); if(v<0) v=-v; return v%limit; }
