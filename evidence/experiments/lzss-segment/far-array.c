extern void far *unpackHandle;
void far ProbeFar(void)
{
    unsigned int far *roots = (unsigned int far *)(((unsigned long)(unsigned int)((unsigned long)unpackHandle >> 16) << 16) | 0x501aL);
    unsigned int far *links = (unsigned int far *)(((unsigned long)(unsigned int)((unsigned long)unpackHandle >> 16) << 16) | 0x521aL);
    int i;
    for (i = 0; i < 0x100; ++i) roots[i] = 0x1000;
    for (i = 0; i < 0x1000; ++i) links[i] = 0x1000;
}
