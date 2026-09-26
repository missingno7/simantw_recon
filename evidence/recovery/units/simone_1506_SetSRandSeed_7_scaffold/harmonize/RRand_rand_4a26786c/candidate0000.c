/* Byte-matched C reconstruction. Modern filename and isolated translation unit.
 * Historical source text and declaration spelling are not uniquely recovered. */
extern int far rand(void);
int RRand(int limit) { int v=rand(); if(v<0) v=-v; return v%limit; }
