#define debugging (*(int near *)0x0864)

void mem_Debugging(int value)
{
    debugging = value;
}
