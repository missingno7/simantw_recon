/* Probe frame and near/far pointer homes for the proven load-lock-unhook preamble. */
extern unsigned int far db_LoadObject(int,int,int);
extern void far *mem_Lock(unsigned int);
extern void far db_UnhookObject(int,int);
int far InitMenu(int object) {
    unsigned int handle;
    char far *block;
    int ok;
    handle=db_LoadObject(object,6,0);
    if(!handle) return 0;
    block=(char far *)mem_Lock(handle);
    ok=(block!=0);
    db_UnhookObject(object,6);
    return ok;
}