/* Byte-matched C reconstruction. Modern filename and isolated translation unit.
 * Historical source text and declaration spelling are not uniquely recovered. */
extern unsigned short FlipWord(unsigned short);
void ExtractWord(void far * far *p,unsigned short far *out) { *out=*(unsigned short far *)*p; *out=FlipWord(*out); *p=(void far *)((unsigned long)*p+2); }
