extern int far setjmp(char far *); extern void far longjmp(char far *,int);
int far RallocFindMem(int seed){ char far state[16]; register int value=seed; int code; code=setjmp(state); if(code==0){ value=value+1; longjmp(state,1); } return value+code; }
