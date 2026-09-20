extern unsigned int near edata[];

int SRand1(unsigned int range)
{
    unsigned int value;

    value = edata[201];
    if (value & 0x8000)
        value = (value << 1) ^ 0x1bf5;
    else
        value <<= 1;
    edata[201] = value;
    return value % range;
}
