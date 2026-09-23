extern void far *unpackHandle;
void far ProbeBased(void)
{
    __segment tree_segment = (__segment)unpackHandle;
    unsigned int __based(tree_segment) *roots = (unsigned int __based(tree_segment) *)0x501a;
    unsigned int __based(tree_segment) *links = (unsigned int __based(tree_segment) *)0x521a;
    int i;
    for (i = 0; i < 0x100; ++i) roots[i] = 0x1000;
    for (i = 0; i < 0x1000; ++i) links[i] = 0x1000;
}
