extern void *memset(void *, int, unsigned);
#pragma intrinsic(memset)
void far Fill(unsigned char *p, unsigned char v, unsigned n) { unsigned i; memset(p, v, n); i = n; if (i) p[0] = v; }
