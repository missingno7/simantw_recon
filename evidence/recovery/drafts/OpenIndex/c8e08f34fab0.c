/*
 * OpenIndex: opens an index file named by sprintf-ing two caller values
 * into a format string, stores the resulting handle in a per-slot record,
 * reads a 20-byte header from the file into that record, allocates a
 * buffer sized from the header's first word * 8, reads that many bytes
 * into the buffer, stores the far pointer in the record, then closes the
 * file handle.
 */
extern int far sprintf(char far *buffer, char far *format, ...);
extern int far pascal _lopen(char far *path, int mode);
extern long far pascal _lread(int handle, void far *buffer, unsigned count);
extern int far pascal _lclose(int handle);
extern void far Punt(char far *message, ...);
void far DosPunt(char far *message);
extern void far *mem_malloc(unsigned int size);

extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define IdxHeader(i) (&AT((i) * 0x7c + 0x745c))
#define IdxDataPtr(i) (*(void far * far *)&AT((i) * 0x7c + 0x7458))
#define IdxHandle(i) (*(int far *)&AT((i) * 0x7c + 0x747e))

void far OpenIndex(int p1, int p2, int idx)
{
    char name[100];
    int handle;
    unsigned size;
    void far *buf;

    sprintf(name, "index%d.%d", p1, p2);
    handle = _lopen(name, 2);
    IdxHandle(idx) = handle;
    if (handle <= 0)
        DosPunt("Can't open index file");
    _lread(handle, IdxHeader(idx), 20);
    size = *(int far *)IdxHeader(idx) << 3;
    buf = mem_malloc(size);
    IdxDataPtr(idx) = buf;
    if (buf == 0)
        Punt("Out of memory");
    _lread(handle, buf, size);
    _lclose(handle);
}
