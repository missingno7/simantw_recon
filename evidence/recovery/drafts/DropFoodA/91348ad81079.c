extern int far TERRAINset;
extern int far FoodA;
extern int far DROPdir;
extern unsigned char __based(__segname("PACK")) pack_buf[];
extern unsigned char near MapA[128][64];

int far DropFoodA(int x, int y)
{
    unsigned char near *cell;
    unsigned char near *scanCell;
    int value;
    int keepSearching;
    int scanX;
    int scanY;
    int rowIndex;
    int rowDelta;

    scanX = x;
    scanY = y;
    cell = &MapA[scanX][scanY];
    value = *cell;

    if (TERRAINset == 1) {
        for (;;) {
            if (value < 4) {
                *cell = (value + 6) << 2;
                FoodA++;
                return 1;
            }

            if (value >= 8 && value < 0x18) {
                value = (value - 8) >> 2;
                continue;
            }

            if (value >= 0x18 && value < 0x27) {
                ++*cell;
                FoodA++;
                return 1;
            }

            if (value >= 0x40)
                return 0;

            keepSearching = 1;
            rowIndex = scanX << 6;
            rowDelta = pack_buf[0x22ba + DROPdir] << 6;
            scanCell = &MapA[scanX][scanY];

            while (keepSearching != 0) {
                value = *scanCell;
                if (value < 4) {
                    *scanCell = (value + 6) << 2;
                    FoodA++;
                    keepSearching = 0;
                }

                scanX += pack_buf[0x22ba + DROPdir];
                rowIndex += rowDelta;
                scanY += pack_buf[0x22be + DROPdir];
                if (scanX < 0 || scanX > 0x7f ||
                    scanY < 0 || scanY > 0x3f)
                    return 1;

                if (keepSearching != 0) {
                    scanCell = (unsigned char near *)MapA + rowIndex + scanY;
                }
            }
            return 1;
        }
    } else {
        if (value >= 0x4b)
            return 0;
        if (value >= 0x48)
            *cell = 0x48;
        else
            ++*cell;
        return 1;
    }
}