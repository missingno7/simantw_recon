/* Load handle words through a named two-word record before making the far bucket pointer. */
struct WinObject { unsigned char reserved[0x20]; unsigned char group; unsigned char pad[3]; unsigned char state; };
struct WinBucket { unsigned char header[0x0c]; int count; unsigned char rest[0x2c-0x0e]; struct WinObject far *objects[256]; };
extern void far win_LockWin(int); extern void far win_UnlockWin(int);
struct HandleWords { unsigned int offset; unsigned int selector; }; extern struct HandleWords near win_handles[];
void far win_MakeGroupSelectable(int objectNumber,int group) { struct HandleWords h; unsigned long raw; int i; int count; struct WinObject far * far *entry; struct WinBucket far *bucket; int window;
 win_LockWin(objectNumber); window=objectNumber>>8; h=win_handles[window]; raw=((unsigned long)h.selector<<16)|h.offset; bucket=(struct WinBucket far *)raw; i=0;
 if(bucket->count>0) { entry=bucket->objects; count=bucket->count; do { if((*entry)->group==(unsigned char)group) (*entry)->state|=2; entry++; } while(++i<count); }
 win_UnlockWin(objectNumber);
}
