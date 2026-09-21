/*
 * CloseIndex: if the index record's dirty flag (slot+0x7a) is set, write
 * the index back to its ".ndx" file (named by the string stored at the
 * slot's start) via _lcreat/_llseek(0)/_lwrite/_lclose -- first the
 * 20-byte header at slot+0x54 (whose leading word is the record count),
 * then, when that count is nonzero, count*8 bytes from the far buffer
 * pointer stored at slot+0x50 -- reporting "Index file missing" through
 * DosPunt on a non-positive create handle.  Either way, the far buffer at
 * slot+0x50 is freed if non-null.  Matches the sibling OpenIndex draft's
 * record layout and match_position byte-array idiom (same unit_context
 * simtwo:9A86): slot = idx*0x7c, absolute field offsets already include
 * the 0x7408 match_position base.
 */
extern int far sprintf(char far *buffer, char far *format, ...);
extern int far pascal _lcreat(char far *path, int attrib);
extern long far pascal _llseek(int handle, long offset, int origin);
extern int far pascal _lwrite(int handle, void far *buffer, unsigned count);
extern int far pascal _lclose(int handle);
void far DosPunt(char far *message);
extern void far mem_free(void far *block);

extern int far match_position[];
#define MP ((unsigned char far *)match_position)
#define AT(off) (MP[off])

void far CloseIndex(int idx)
{
    int recBase;
    int handle;
    char name[100];
    int count;
    void far *buf;

    recBase = idx * 0x7c;
    if (*(int far *)&AT(recBase + 0x7482) != 0) {
        sprintf(name, "%s.ndx", &AT(recBase + 0x7408));
        handle = _lcreat(name, 0);
        *(int far *)&AT(recBase + 0x747e) = handle;
        if (handle <= 0)
            DosPunt("Index file missing");
        _llseek(handle, 0L, 0);
        _lwrite(handle, &AT(recBase + 0x745c), 20);
        count = *(int far *)&AT(recBase + 0x745c);
        if (count != 0)
            _lwrite(handle, *(void far * far *)&AT(recBase + 0x7458), count << 3);
        _lclose(handle);
    }
    buf = *(void far * far *)&AT(recBase + 0x7458);
    if (buf != 0)
        mem_free(buf);
}
