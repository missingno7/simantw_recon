extern int near editMessage[];

void DialogDone(void)
{
    if (--editMessage[98] < -1)
        editMessage[98] = -1;
}
