extern unsigned long far pascal GetTickCount(void);
void WaitHundredths(int count)
{
    unsigned long deadline;

    deadline = 10 * count + GetTickCount();
    while (GetTickCount() < deadline)
        ;
}
