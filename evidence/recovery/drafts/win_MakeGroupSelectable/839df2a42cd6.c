struct WinObject { unsigned char reserved[0x20]; unsigned char group; unsigned char pad[3]; unsigned char state; };
struct WinBucket { unsigned char header[0x0c]; int count; unsigned char rest[0x2c-0x0e]; struct WinObject far *objects[256]; };
extern void far win_LockWin(int);
extern void far win_UnlockWin(int);
extern unsigned int near win_handles[];
/* Set the matching window object's selectable bit using the two handle words. */
void far win_MakeGroupSelectable(int objectNumber,int group) { unsigned int window,idx,off,sel; unsigned long raw; int i,count; unsigned char wanted; struct WinBucket far *bucket; struct WinObject far * far *entry; struct WinObject far *obj; win_LockWin(objectNumber); window=(unsigned int)objectNumber>>8; idx=window+window; off=win_handles[idx]; sel=win_handles[idx+1]; raw=((unsigned long)sel<<16)|off; bucket=(struct WinBucket far *)raw; wanted=(unsigned char)group; for(i=0;i<bucket->count;i++){ obj=bucket->objects[i]; if(obj->group==wanted) obj->state|=2; } win_UnlockWin(objectNumber); }
