struct Event { int object; int x; }; extern void far SetPause(int); extern int far GetEvent(struct Event near *); extern void far KeepPtr(int near *);
int far RallocFindMem(int seed){ struct Event event; int old=seed; int choice=-1; int i; SetPause(1); KeepPtr(&old); KeepPtr(&choice); for(i=0;i<4 && GetEvent(&event);i++){ if(event.object) choice=event.object; } return old+choice+i; }
