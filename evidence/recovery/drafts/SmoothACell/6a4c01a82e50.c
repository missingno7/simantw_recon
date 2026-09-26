/* Smooth the active ant-edit cell from its four neighbours and center,
 * preserving the current plane-specific cell array. */
extern unsigned char far Dx8[];


#define READ_SM(X, Y, VALUE) \
    switch (Dx8[0x8605]) { \
    case 0: VALUE = Dx8[((X) << 5) + (Y) + 0x62d2]; break; \
    case 1: VALUE = Dx8[((X) << 5) + (Y) + 0x6ad2]; break; \
    case 2: VALUE = Dx8[((X) << 5) + (Y) + 0x72d2]; break; \
    case 3: VALUE = Dx8[((X) << 5) + (Y) + 0x7ad2]; break; \
    case 4: VALUE = Dx8[((X) << 5) + (Y) + 0x52d2]; break; \
    }

#define WRITE_SM(X, Y, VALUE) \
    switch (Dx8[0x8605]) { \
    case 0: Dx8[((X) << 5) + (Y) + 0x62d2] = (VALUE); break; \
    case 1: Dx8[((X) << 5) + (Y) + 0x6ad2] = (VALUE); break; \
    case 2: Dx8[((X) << 5) + (Y) + 0x72d2] = (VALUE); break; \
    case 3: Dx8[((X) << 5) + (Y) + 0x7ad2] = (VALUE); break; \
    case 4: Dx8[((X) << 5) + (Y) + 0x52d2] = (VALUE); break; \
    }

void far SmoothACell(int x, int y)
{
    int total;
    volatile unsigned char value;
    int center;
    int result;

    total = 0;
    if (x >= 0 && x <= 63 && y - 1 >= 0 && y - 1 <= 31) {
        READ_SM(x, y - 1, value);
        total += value;
    } else {
        total += -1;
    }
    if (x + 1 >= 0 && x + 1 <= 63 && y >= 0 && y <= 31) {
        READ_SM(x + 1, y, value);
        total += value;
    } else {
        total += -1;
    }
    if (x >= 0 && x <= 63 && y + 1 >= 0 && y + 1 <= 31) {
        READ_SM(x, y + 1, value);
        total += value;
    } else {
        total += -1;
    }
    if (x - 1 >= 0 && x - 1 <= 63 && y >= 0 && y <= 31) {
        READ_SM(x - 1, y, value);
        total += value;
    } else {
        total += -1;
    }

    if (x >= 0 && x <= 63 && y >= 0 && y <= 31) {
        READ_SM(x, y, center);
        result = ((total / 4) + center) / 2;
        if (result > 255)
            result = 255;
        WRITE_SM(x, y, result);
    }
}
