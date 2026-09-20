#define debugFlag (*(int near *)0x08f2)

void SetDebugFlag(void)
{
    debugFlag = 0;
}
