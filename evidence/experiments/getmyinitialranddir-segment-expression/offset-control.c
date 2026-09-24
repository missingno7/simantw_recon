/* Control: the prior near-pointer cast style reaches the far symbol offset. */
extern int far match_position[];
extern void far TakeSelector(unsigned int selector);
void far ProbeSelector(void)
{
    TakeSelector((unsigned int)(int near *)match_position);
}