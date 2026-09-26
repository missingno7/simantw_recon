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
    volatile int savedRow;
    unsigned char tile;
    unsigned int near *words;

    for (words = (unsigned int near *)MapA;
         words <= (unsigned int near *)&MapA[0x1a40];
         words += 0x20) {
        for (word = 0; word < 0x20; ++word)
            words[word] = 0x0303;
    }

    for (row = 0; row <= 0x1a40; row += 0x40) {
        savedRow = row;
        for (column = 0; column <= 0x3f; ++column) {
            if (SRand1(200) != 0) {
                tile = (unsigned char)(SRand1(2) + 0x3e);
                MapA[row + column] = tile;
            }
        }
    }

    for (words = (unsigned int near *)&MapA[0x1a80];
         words <= (unsigned int near *)&MapA[0x1a80];
         words += 0x20) {
        for (word = 0; word < 0x20; ++word)
            words[word] = 0x7c7c;
    }
    for (words = (unsigned int near *)&MapA[0x1a00];
         words <= (unsigned int near *)&MapA[0x1a40];
         words += 0x20) {
        for (word = 0; word < 0x20; ++word)
            words[word] = 0x7b7b;
    }
    for (words = (unsigned int near *)&MapA[0x1a80];
         words <= (unsigned int near *)&MapA[0x1fc0];
         words += 0x20) {
        for (word = 0; word < 0x20; ++word)
            words[word] = 0x6464;
    }

    MakeOutletH(0x71, 0x23);
    DROPdir = 3;
}
