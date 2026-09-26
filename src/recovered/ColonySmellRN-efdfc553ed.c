/* Ages the 0x20-byte scent bands through the Dx8 segment. */
extern unsigned char far Dx8[];
void near ColonySmellRN(void) {
    int row, cell;
    for (row = 0; row < 64; ++row)
        for (cell = 0; cell < 32; ++cell)
            if (Dx8[0x72d2 + row * 32 + cell] != 0)
                --Dx8[0x72d2 + row * 32 + cell];
}
