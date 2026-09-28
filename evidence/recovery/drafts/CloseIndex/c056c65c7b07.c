extern int far sprintf(char far *, char far *, ...);
extern int far pascal _lcreat(char far *, int);
extern long far pascal _llseek(int, long, int);
extern int far pascal _lwrite(int, void far *, unsigned);
extern int far pascal _lclose(int);
void far DosPunt(char far *);
extern void far mem_free(void far *);
extern int far match_position[];
#define MP ((unsigned char far *)match_position)
#define AT(off) (MP[off])
struct OpenDB { char name[0x50]; void far *indexTable; int recordCount; unsigned char pad1[0x16]; int count; long freeBytes; long wastedBytes; int pad2; int file; int dirty; };
extern struct OpenDB far openDBData[];
void far CloseIndex(int idx) { int base; int handle; char name[100]; int count; void far *header; void far * volatile buffer; base=idx*0x7c; sprintf(name,"%s.ndx",openDBData[idx].name); if(openDBData[idx].dirty==0) goto release; handle=_lcreat(name,0); openDBData[idx].pad2=handle; if(handle<=0) DosPunt("Index file missing"); _llseek(handle,0L,0); header=&openDBData[idx].recordCount; _lwrite(handle,header,20); count=*(int far *)header; if(count) _lwrite(handle,openDBData[idx].indexTable,count<<3); _lclose(handle); release: buffer=openDBData[idx].indexTable; if(buffer) mem_free(buffer); }
