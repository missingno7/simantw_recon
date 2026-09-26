struct WinObject { unsigned char reserved[0x20]; unsigned char group; unsigned char pad[3]; unsigned char state; };
struct WinBucket { unsigned char header[0x0c]; int count; unsigned char rest[0x2c-0x0e]; struct WinObject far *objects[256]; };
extern void far win_LockWin(int);
extern void far win_UnlockWin(int);
extern unsigned int near win_handles[];
/* Reconstruct the locked window bucket and set the requested object's selectable bit. */
void far win_MakeGroupSelectable(int objectNumber,int group) { unsigned int off, sel, ti; unsigned long raw; int i,count,window; struct WinObject far * far *entry; struct WinBucket far *bucket; int saved; saved=objectNumber; win_LockWin(saved); window=saved>>8; ti=window*2; off=win_handles[ti]; sel=win_handles[ti+1]; raw=((unsigned long)sel<<16)|off; bucket=(struct WinBucket far *)raw; i=0; if(bucket->count>0){ entry=bucket->objects; count=bucket->count; do { if((*entry)->group==(unsigned char)group) (*entry)->state|=2; entry++; } while(++i<count); } win_UnlockWin(saved); }
