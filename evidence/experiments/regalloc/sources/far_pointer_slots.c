extern void far Probe(void);
int far RallocFindMem(int far *input) {
 int far *slots[1]; int before;
 slots[0]=input; before=*slots[0]; Probe();
 *slots[0]=(int)(*slots[0]+before+1);
 return *slots[0];
}
