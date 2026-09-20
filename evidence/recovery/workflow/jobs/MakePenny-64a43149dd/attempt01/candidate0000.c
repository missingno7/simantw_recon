/*
 * Stamp the private 3-by-3 penny template into the map.  Map rows advance by
 * 0x40 bytes; template bytes advance by three bytes for each inner column.
 */
extern unsigned char near PennyTemplate[];
extern unsigned char near Map[];

void MakePenny(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 3; ++outer) {
        for (inner = 0; inner < 3; ++inner)
            Map[(row << 6) + column + (outer << 6) + inner] =
                PennyTemplate[0x2356 + outer + inner * 3];
    }
}
