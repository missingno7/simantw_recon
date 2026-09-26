int far RallocFindMem(int far *fp, int near *np, int x) {
 int far *f=fp; int near *n=np; int a=*n+x; int b=*f;
 *f=(int)(b+a); return *n+*f;
}
