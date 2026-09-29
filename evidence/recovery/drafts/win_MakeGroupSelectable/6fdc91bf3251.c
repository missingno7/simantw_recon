struct WinObject { unsigned char reserved[0x20]; unsigned char group; unsigned char pad[3]; unsigned char state; };
struct WinBucket { unsigned char header[0x0c]; int count; unsigned char rest[0x2c-0x0e]; struct WinObject far *objects[256]; };
extern void far win_LockWin(int);
extern void far win_UnlockWin(int);
extern struct WinBucket far * near win_handles[];
/* Set the matching window object's selectable bit using the two handle words. */
void far win_MakeGroupSelectable(int objectNumber,int group) { volatile int window; int idx; int i,count; unsigned int off,sel; unsigned long raw; struct WinBucket far *bucket; struct WinObject far * far *entry; struct WinObject far *obj; win_LockWin(objectNumber); window=objectNumber & 0xff00; idx=objectNumber >> 8; off=((unsigned int near *)win_handles)[idx*2]; sel=((unsigned int near *)win_handles)[idx*2+1]; raw=((unsigned long)sel<<16)|off; bucket=(struct WinBucket far *)raw; for(i=0;i<bucket->count;i++){ obj=bucket->objects[i]; if(obj->group==(unsigned char)group) obj->state|=2; } win_UnlockWin(objectNumber); }


