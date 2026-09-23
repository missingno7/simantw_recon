/* Segment 9 selector word at unpackHandle+2 supplies the tree segment;
   historical stores start at offsets 0x501a and 0x521a. */
extern void far *unpackHandle;
#define roots ((unsigned int __based((__segment)unpackHandle) *)0x501a)
#define links ((unsigned int __based((__segment)unpackHandle) *)0x521a)
void far InitTree(void)
{
    int i;
    for (i=0;i<0x100;++i) roots[i]=0x1000;
    for (i=0;i<0x1000;++i) links[i]=0x1000;
}
