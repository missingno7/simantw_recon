/* Byte-matched C reconstruction. Modern filename and isolated translation unit.
 * Historical source text and declaration spelling are not uniquely recovered. */
struct H { void far *data; unsigned short reserved; unsigned long size; unsigned long age; unsigned short type; };
unsigned long RallocSize(struct H *p) { return p->size; }
