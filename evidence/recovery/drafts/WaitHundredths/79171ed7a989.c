extern unsigned long far pascal GetTickCount(void);

void WaitHundredths(unsigned int count)
{
    unsigned long deadline;

    deadline = GetTickCount() + 10 * count;
    while (GetTickCount() < deadline)
        ;
}
