extern __segment near unpackTreeSegment;
extern unsigned int __based(unpackTreeSegment) roots[];
extern unsigned int __based(unpackTreeSegment) links[];
void far ProbeNamedSegment(void)
{
    int i;
    for (i = 0; i < 0x100; ++i) roots[i] = 0x1000;
    for (i = 0; i < 0x1000; ++i) links[i] = 0x1000;
}
