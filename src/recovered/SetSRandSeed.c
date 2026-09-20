extern int near edata[];

void SetSRandSeed(int value)
{
    edata[201] = value;
}
