extern void far * near unpackHandle;
extern unsigned int __based((__segment)unpackHandle) roots[];
extern unsigned int __based((__segment)unpackHandle) links[];
void far ProbeNamed(void)
{
    int i;
    for (i = 0; i < 0x100; ++i) roots[i] = 0x1000;
    for (i = 0; i < 0x1000; ++i) links[i] = 0x1000;
}
