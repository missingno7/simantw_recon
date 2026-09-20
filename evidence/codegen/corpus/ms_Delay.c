extern unsigned long far pascal GetTickCount(void);

void ms_Delay(unsigned int delay)
{
    unsigned long deadline;

    deadline = GetTickCount();
    deadline += delay;
    while (GetTickCount() < deadline)
        ;
}
