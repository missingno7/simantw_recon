/* Ages each nonzero byte in the Dx8 scent window. */
extern unsigned char far Dx8[];
void near ColonySmellRN(void) {
    int row, cell;
    unsigned char far *table;
    table = Dx8;
    for (row = 0x72d2; row < 0x7ad2; row += 0x20)
        for (cell = 0; cell < 0x20; ++cell)
            if (table[row + cell] != 0)
                --table[row + cell];
}
