extern unsigned long far GlobalCompact(unsigned long); extern int far lowMemoryReported; extern void far SetPause(int);
void far RallocFindMem(unsigned long needed){ if(GlobalCompact(0xffffffffUL)>=needed){ switch(lowMemoryReported){ case 0: SetPause(1); lowMemoryReported=1; break; default: break; } } }
