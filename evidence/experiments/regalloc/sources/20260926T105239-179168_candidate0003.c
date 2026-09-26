extern void far PausePoint(void); extern void far ObservePtr(int near *);
int far RallocFindMem(int p,int q){ int a=p+1; int b=q+2; PausePoint(); ObservePtr(&a); return a+b; }
