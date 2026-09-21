/*
 * SetQueenTail installs a queen-tail life entry.  The requested life type
 * 0xff is the historical shorthand for 0xfe.  The table index is adjusted
 * in its low byte, then the two far table bytes at offsets +8 and +0 are
 * added to the caller's Y and X coordinates before the four values are sent
 * to the same-segment SetLife helper.
 */
extern unsigned char far queenTailY[];
extern unsigned char far queenTailX[];
extern void near SetLife(int kind, int x, int y, int tableType);

void SetQueenTail(int kind, int x, int y, unsigned char tableIndex,
                  int tableType)
{
    int lifeType;

    lifeType = tableType;
    if (tableType == 0xff)
        lifeType = 0xfe;

    tableIndex ^= 4;
    SetLife(kind, x + queenTailX[tableIndex],
            y + queenTailY[tableIndex + 8], lifeType);
}
