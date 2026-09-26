struct Event { int object; int x; }; extern void far SetPause(int); extern int far GetEvent(struct Event near *); extern int far Touch(int);
int far RallocFindMem(int seed){ struct Event event; int old=seed; int choice=-1; int i; SetPause(1); for(i=0;i<4 && GetEvent(&event);i++){ if(event.object) choice=event.object; else old=Touch(old); } return old+choice+i; }
