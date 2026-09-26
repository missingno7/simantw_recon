/* R1 controlled residue hypothesis. */
/*
 * CreateIndex: create (truncate/open) index idx's ".ndx" file from a
 * sprintf'd "<name>.ndx" path, store the handle at slot+0x747e (a
 * DosPunt warning with the sprintf buffer and errno on a non-positive
 * handle), zero the 20-byte header at slot+0x745c (count, an unknown
 * companion word, three long fields, and two more words), then _lwrite
 * that header back from the file (20 bytes); when the header's leading
 * word (record count) is nonzero, mem_malloc(count*8,"index") and store
 * the far result at slot+0x50/+0x52, otherwise zero those two fields.
 * Finally _lclose the handle.  Matches the sibling CloseIndex/OpenIndex
 * record layout and match_position byte-array idiom (same unit_context
 * simtwo:9A86); field offsets already include the 0x7408 match_position
 * base.
 */
struct IndexHeader {
    int count;
    int field2;
    long stat1;
    long stat2;
    long stat3;
    int field8;
    int field9;
};

extern int far sprintf(char far *buffer, char far *format, ...);
extern int far pascal _lcreat(char far *path, int attrib);
extern long far pascal _lwrite(int handle, void far *buffer, unsigned count);
extern int far pascal _lclose(int handle);
extern int near errno;
void far DosPunt(char far *message, ...);
extern void far *mem_malloc(unsigned int size, char far *tag);

extern int far match_position[];
#define MP ((unsigned char far *)match_position)
#define AT(off) (MP[off])

void far CreateIndex(char far *name, int idx)
{
    char buf[100];
    int recBase;
    int handle;
    int far *hdr;
    unsigned size;
    void far *data;

    { int slot = idx; recBase = slot * 0x7c; }
    sprintf(buf, "%s.ndx", name);
    handle = _lcreat(buf, 0);
    match_position[idx * 62 + 14911] = handle;
    if (handle <= 0)
        DosPunt("Can't create index file", buf, errno);

    hdr = &match_position[idx * 62 + 14894];
    hdr[0] = 0; hdr[1] = 0; hdr[2] = 0; hdr[3] = 0; hdr[4] = 0;
    hdr[5] = 0; hdr[6] = 0; hdr[7] = 0; hdr[8] = 0; hdr[9] = 0;

    _lwrite(handle, hdr, 0x14);
    size = (unsigned)(hdr[0] * 8);
    if (hdr[0] != 0) {
        data = mem_malloc(size, "index");
        *(void far * far *)&match_position[idx * 62 + 14892] = data;
    } else {
        *(void far * far *)&match_position[idx * 62 + 14892] = 0;
    }
    _lclose(handle);
}
