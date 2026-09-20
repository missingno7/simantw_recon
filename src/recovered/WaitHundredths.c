extern unsigned long far TickCount(void);

void WaitHundredths(unsigned int hundredths)
{
    unsigned long target;
    unsigned int delay;
    target = TickCount();
    delay = (hundredths << 2) + hundredths;
    delay <<= 1;
    target += delay;
    while (TickCount() < target) {
    }
}
