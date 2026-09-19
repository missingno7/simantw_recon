/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
int IsThisPebble(int kind, int value)
{
    if (kind <= 1) {
        if (kind == 1) {
            if (value >= 0x51 && value <= 0x53) return 1;
        }
    } else {
        if (value >= 0x30 && value <= 0x31) return 1;
    }
    return 0;
}
