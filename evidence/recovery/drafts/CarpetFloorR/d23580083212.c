/* Initialize the red colony's carpet rows, then scatter the two carpet
 * variants through MapA and mark the shared drop direction. */
extern unsigned char near MapA[];
extern int far DROPdir;
extern int far SRand1(int n);
extern void far MakeOutletH(int x, int y);

void far CarpetFloorR(void)
{
    int row;
    int column;
    int word;
    unsigned char tile;

    for (row = 0; row <= 0x1a40; row += 0x40) {
        for (word = 0; word < 0x20; ++word)
            ((unsigned int near *)MapA)[(row >> 1) + word] = 0x0303;
    }

    for (row = 0; row <= 0x1a40; row += 0x40) {
        for (column = 0; column <= 0x3f; ++column) {
            if (SRand1(200) != 0) {
                tile = (unsigned char)(SRand1(2) + 0x3e);
                MapA[row + column] = tile;
            }
        }
    }

    for (row = 0x1a80; row <= 0x1a80; row += 0x40) {
        for (word = 0; word < 0x20; ++word)
            ((unsigned int near *)MapA)[(row >> 1) + word] = 0x7c7c;
    }
    for (row = 0x1a00; row <= 0x1a40; row += 0x40) {
        for (word = 0; word < 0x20; ++word)
            ((unsigned int near *)MapA)[(row >> 1) + word] = 0x7b7b;
    }
    for (row = 0x1a80; row <= 0x1fc0; row += 0x40) {
        for (word = 0; word < 0x20; ++word)
            ((unsigned int near *)MapA)[(row >> 1) + word] = 0x6464;
    }

    MakeOutletH(0x71, 0x23);
    DROPdir = 3;
}
