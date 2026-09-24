/* Isolated C7 test: can __segname("PACK") be used as a word expression? */
extern void far TakeSelector(unsigned int selector);
void far ProbeSegmentName(void)
{
    TakeSelector(__segname("PACK"));
}