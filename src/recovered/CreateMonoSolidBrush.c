/* Byte-matched C reconstruction. Modern filename and isolated translation unit.
 * Historical source text and declaration spelling are not uniquely recovered. */
extern unsigned far pascal CreateSolidBrush(unsigned long);
unsigned CreateMonoSolidBrush(unsigned char c) { switch(c&0x70) { case 0: return CreateSolidBrush(0L); case 0x10: return CreateSolidBrush(0x606060L); case 0x20: return CreateSolidBrush(0x808080L); case 0x30: return CreateSolidBrush(0xa0a0a0L); case 0x50: return CreateSolidBrush(0xc0c0c0L); case 0x60: return CreateSolidBrush(0x202020L); default: return CreateSolidBrush(0xffffffL); } }
