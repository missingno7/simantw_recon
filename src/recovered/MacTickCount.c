/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern unsigned long TickCount(void);

unsigned long MacTickCount(void)
{
    unsigned long value;
    value = TickCount();
    return value * 3;
}
