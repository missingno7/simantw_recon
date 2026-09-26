/*
 * MakeKitchenWall: fill the first 24 bytes of each MapA row with 0x62,
 * clear the remaining 40 bytes, lay three 0x68 posts at columns 0, 8,
 * and 16, then update the upper 24 columns of every eighth row and the
 * column at 23.  Create the two vertical outlets and set DROPdir to 2.
 */
extern unsigned char near MapA[128][64];
extern int far DROPdir;
extern void far MakeOutletV(int x, int y);

void far MakeKitchenWall(void)
{
    unsigned int near *p;
    int row, col, word;

    for (p = (unsigned int near *)MapA;
         p <= (unsigned int near *)&MapA[127][0]; p += 0x20) {
        for (word = 0; word < 12; ++word)
            p[word] = 0x6262;
    }
    for (p = (unsigned int near *)&MapA[0][24];
         p <= (unsigned int near *)&MapA[127][24]; p += 0x20) {
        for (word = 0; word < 20; ++word)
            p[word] = 0;
    }

    for (col = 0; col < 24; col += 8) {
        for (row = 0; row < 128; ++row)
            MapA[row][col] = 0x68;
    }

    for (row = 0; row < 128; row += 8) {
        for (col = 0; col < 24; ++col) {
            if (MapA[row][col] == 0x62)
                MapA[row][col] = 0x66;
            else
                MapA[row][col] = 0x67;
        }
    }

    for (row = 0; row < 128; ++row) {
        if (MapA[row][23] == 0x62)
            MapA[row][23] = 0x68;
        else
            MapA[row][23] = 0x69;
    }

    MakeOutletV(0x24, 2);
    MakeOutletV(0x54, 2);
    DROPdir = 2;
}
