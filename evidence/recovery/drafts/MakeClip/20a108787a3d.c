/*
 * Hypothesis: MakeClip stamps a 3 by 3 sparse clip mask into MapA.
 * The mask is stored in the original SIMONE data group at 0x2360 and is
 * laid out by columns (one byte per row, then three bytes to the next row).
 * Zero mask entries leave the destination unchanged; each outer iteration
 * advances one map row (64 bytes).
 */
extern unsigned char near MapA[];
static unsigned char near ClipMask[9];

void MakeClip(int x, int y)
{
    int row;
    int col;
    unsigned char near *mask;

    for (row = 0; row < 3; ++row) {
        col = 0;
        mask = ClipMask + row;
        while (col < 3) {
            if (*mask != 0)
                MapA[(x << 6) + y + col] = *mask;
            mask += 3;
            ++col;
        }
        x++;
    }
}
