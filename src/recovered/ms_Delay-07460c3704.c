/* Busy-wait until the unsigned GetCurrentTime tick count reaches the
 * deadline formed from the current time plus the requested delay. */
extern unsigned long far pascal GetTickCount(void);

void ms_Delay(int delay)
{
    unsigned long deadline;

    deadline = GetTickCount() + delay;
    while (GetTickCount() < deadline)
        ;
}
