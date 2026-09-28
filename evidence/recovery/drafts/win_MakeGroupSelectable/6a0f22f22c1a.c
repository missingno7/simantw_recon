struct WinObject { unsigned char reserved[0x20]; unsigned char group; unsigned char pad[3]; unsigned char state; };
struct WinBucket { unsigned char header[0x0c]; int count; unsigned char rest[0x2c-0x0e]; struct WinObject far *objects[256]; };
extern void far win_LockWin(int);
extern void far win_UnlockWin(int);
extern unsigned int near win_handles[];
/* Reconstruct the locked window bucket and set the requested object's selectable bit. */
void far win_MakeGroupSelectable(int objectNumber,int group) { int window; int i, count; struct WinObject far * far *entry; struct WinBucket far *bucket; unsigned int off, sel, ti; unsigned long raw; win_LockWin(objectNumber); window=objectNumber>>8; ti=window*2; off=win_handles[ti]; sel=win_handles[ti+1]; raw=((unsigned long)sel<<16)|off; bucket=(struct WinBucket far *)raw; count=bucket->count; i=0; while(i<count){ struct WinObject far *obj; obj=bucket->objects[i]; if(obj->group==(unsigned char)group) obj->state|=2; i++; } win_UnlockWin(objectNumber); }
