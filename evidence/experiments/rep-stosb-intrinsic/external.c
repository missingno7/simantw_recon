extern void *memset(void *, int, unsigned);
void far Fill(unsigned char *p, unsigned char v, unsigned n) { memset(p, v, n); }
