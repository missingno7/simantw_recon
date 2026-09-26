/* R1 remove volatile from the record-base home. */
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
void far CloseIndex(int idx) { int recBase; char name[100]; long count; void far *header; void far *buf; recBase = idx * 0x7c; sprintf(name, "%s.ndx", &AT(recBase + 0x7408));
if (*(int far *)&AT(recBase + 0x7482) == 0) goto release; { register int handle; handle = _lcreat(name, 0); *(int far *)&AT(recBase + 0x747e) = handle; if (handle <= 0) DosPunt("Index file missing"); _llseek(handle, 0L, 0); header = (void far *)&AT(recBase + 0x745c); _lwrite(handle, header, 20); count = *(int far *)header; if (count != 0) _lwrite(handle, *(void far * far *)&AT(recBase + 0x7458), count << 3); _lclose(handle);
} release: buf = *(void far * far *)&AT(recBase + 0x7458); if (buf != 0) mem_free(buf); }
