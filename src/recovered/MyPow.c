/* Byte-matched C reconstruction. Modern filename and isolated translation unit.
 * Historical source text and declaration spelling are not uniquely recovered. */
unsigned long MyPow(unsigned long b,unsigned long n) { unsigned long v,i; if(n==0) return 1; v=1; for(i=1;i<=n;i++) v*=b; return v; }
