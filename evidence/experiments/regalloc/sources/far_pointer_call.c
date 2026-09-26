extern void far Probe(void);
int far RallocFindMem(int far *input) {
 int far *p=input; int before=*p;
 Probe();
 *p=(int)(*p+before+1);
 return *p;
}
