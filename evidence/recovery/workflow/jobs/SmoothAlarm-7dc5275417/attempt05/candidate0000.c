extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])

void far SmoothAlarm(void)
{
    int col;
    int idx;
    int row;
    int sum;
    int val;

    for (idx = 0; idx < 0x800; idx += 0x20) {
        row = idx;
        for (col = 0; col < 0x20; col++)
            AT(idx + col + 0x4ad2) = AT(idx + col + 0x52d2);
    }

    for (idx = 0, row = 0; idx < 0x800; idx += 0x20, row++) {
        for (col = 0; col < 0x20; col++) {
            sum = 0;
            if (idx > 0)
                sum += AT(idx - 0x20 + col + 0x4ad2);
            if (col > 0)
                sum += AT(col - 1 + idx + 0x4ad2);
            if (idx < 0x7e0)
                sum += AT(col + 0x20 + idx + 0x4ad2);
            if (col < 0x1f)
                sum += AT(col + 1 + idx + 0x4ad2);
            sum >>= 2;
            val = AT(idx + col + 0x4ad2);
            val = (val + sum) >> 1;
            if (val > 8)
                AT(idx + col + 0x52d2) = val;
            else
                AT(idx + col + 0x52d2) = 0;
        }
    }
}
