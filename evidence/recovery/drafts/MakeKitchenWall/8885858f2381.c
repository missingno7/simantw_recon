/*
 * MakeKitchenWall fills 24 bytes at the start of every MapA row with 0x62,
 * clears the remaining 40 bytes, sets three post columns, changes the first
 * 24 cells of every eighth row, and updates column 23 across the map. It then
 * creates both outlets and marks DROPdir as 2.
 */
extern unsigned char near MapA[128 * 64];
extern int far DROPdir;
extern void far MakeOutletV(int x, int y);

void far MakeKitchenWall(void)
{
    unsigned int near *p;
    unsigned int rowOffset, rowNumber, column, word;

    for (p = (unsigned int near *)MapA;
         p <= (unsigned int near *)&MapA[127 * 64]; p += 0x20)
        for (word = 0; word < 12; ++word) p[word] = 0x6262;
    for (p = (unsigned int near *)&MapA[24];
         p <= (unsigned int near *)&MapA[127 * 64 + 24]; p += 0x20)
        for (word = 0; word < 20; ++word) p[word] = 0;

    for (column = 0; column < 24; column += 8)
        for (rowNumber = 0; rowNumber < 128; ++rowNumber)
            MapA[rowNumber * 64 + column] = 0x68;

    rowOffset = 0;
    rowNumber = 0;
    do {
        for (column = 0; column < 24; ++column) {
            if (MapA[rowOffset + column] == 0x62)
                MapA[rowOffset + column] = 0x66;
            else
                MapA[rowOffset + column] = 0x67;
        }
        rowOffset += 0x200;
        rowNumber += 8;
    } while (rowOffset < 0x2000);

    for (rowNumber = 0; rowNumber < 128; ++rowNumber) {
        if (MapA[rowNumber * 64 + 23] == 0x62)
            MapA[rowNumber * 64 + 23] = 0x68;
        else
            MapA[rowNumber * 64 + 23] = 0x69;
    }
    MakeOutletV(0x24, 2);
    MakeOutletV(0x54, 2);
    DROPdir = 2;
}

/* continuation round 01 width/narrowing variant 1 */
