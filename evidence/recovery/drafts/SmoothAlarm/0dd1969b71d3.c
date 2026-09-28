extern unsigned char far Dx8[];
#define AT(off) Dx8[off]

void near SmoothAlarm(void)
{
    int row;
    int col;
    int sum;
    int val;

    for (row = 0; row < 0x40; row++) {
        for (col = 0; col < 0x20; col++)
            AT(row * 0x20 + col + 0x4ad2) = AT(row * 0x20 + col + 0x52d2);
    }

    for (row = 0; row < 0x40; row++) {
        for (col = 0; col < 0x20; col++) {
            sum = 0;
            if (row > 0)
                sum = AT((row - 1) * 0x20 + col + 0x4ad2);
            if (col > 0)
                sum += AT(row * 0x20 + col - 1 + 0x4ad2);
            if (row < 0x3f)
                sum += AT((row + 1) * 0x20 + col + 0x4ad2);
            if (col < 0x1f)
                sum += AT(row * 0x20 + col + 1 + 0x4ad2);
            sum >>= 2;
            {
                int cellIndex;
                cellIndex = row * 0x20 + col;
                val = AT(cellIndex + 0x4ad2);
                val = (val + sum) >> 1;
                if (val > 8)
                    AT(cellIndex + 0x52d2) = val;
                else
                    AT(cellIndex + 0x52d2) = 0;
            }
        }
    }
}
