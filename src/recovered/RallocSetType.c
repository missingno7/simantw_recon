/* Byte-matched C reconstruction. Modern filename and isolated translation unit.
 * Historical source text and declaration spelling are not uniquely recovered. */
struct H { void far *data; unsigned short reserved; unsigned long size; unsigned long age; unsigned short type; };
void RallocSetType(struct H *p,int type) { p->type=type; }
