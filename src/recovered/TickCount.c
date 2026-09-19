/* Candidate reconstruction of the Windows tick-count conversion wrapper. */
extern unsigned long far pascal GetTickCount(void);

unsigned long TickCount(void)
{
    return GetTickCount() / 55L;
}
