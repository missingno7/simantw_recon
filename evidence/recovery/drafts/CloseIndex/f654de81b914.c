struct OpenDB { char name[0x50]; void far *indexTable; int recordCount; unsigned char pad1[0x16]; int count; long freeBytes; long wastedBytes; int pad2; int file; int dirty; };
extern struct OpenDB far openDBData[];
extern int far sprintf(char far *, char far *, ...);
extern int far pascal _lcreat(char far *, int);
extern long far pascal _llseek(int, long, int);
extern int far pascal _lwrite(int, void far *, unsigned);
extern int far pascal _lclose(int);
extern void far DosPunt(char far *);
extern void far mem_free(void far *);
void far CloseIndex(int idx) { struct OpenDB far *db; int handle; char name[100]; int count; void far *buf; db = &openDBData[idx]; sprintf(name, "%s.ndx", db->name); if (db->dirty) { handle = _lcreat(name, 0); db->pad2 = handle; if (handle <= 0) DosPunt("Index file missing"); _llseek(handle, 0L, 0); _lwrite(handle, &db->recordCount, 20); buf = db->indexTable; count = *(int far *)buf; if (count != 0) _lwrite(handle, buf, count * 8); _lclose(handle); } buf = db->indexTable; if (buf != 0) mem_free(buf); }
