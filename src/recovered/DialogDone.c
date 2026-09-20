#define dialogCount (*(int near *)0x150a)

void DialogDone(void)
{
    --dialogCount;
    if (dialogCount < -1) dialogCount = -1;
}
