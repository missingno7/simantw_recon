/* Treatment: PACK selector is expressed with MSC's __segname operator. */
extern int far match_position[];
extern void far TakeSelector(unsigned int selector);
void far ProbeSelector(void)
{
    TakeSelector(__segname("PACK"));
}