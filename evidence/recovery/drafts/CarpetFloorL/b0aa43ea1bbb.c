/*
 * CarpetFloorL fills the entrance and room rows with four observed tile
 * runs, then randomizes each cell in rows 23..127 when SRand1(200) is zero.
 * Finally it opens the east outlet and marks DROPdir as 1.
 */
extern unsigned char near MapA[128][64];
extern int far DROPdir;
extern int far SRand1(int range);
extern void far MakeOutletH(int x, int y);

void far CarpetFloorL(void)
{
    unsigned int near *words;
    int word;
    int row;
    int column;

    for (words = (unsigned int near *)MapA;
         words <= (unsigned int near *)&MapA[20][0]; words += 0x20) {
        for (word = 0; word < 0x20; ++word)
            words[word] = 0x6464;
    }
    for (words = (unsigned int near *)&MapA[21][0];
         words <= (unsigned int near *)&MapA[21][0]; words += 0x20) {
        for (word = 0; word < 0x20; ++word)
            words[word] = 0x7a7a;
    }
    for (words = (unsigned int near *)&MapA[22][0];
         words <= (unsigned int near *)&MapA[23][0]; words += 0x20) {
        for (word = 0; word < 0x20; ++word)
            words[word] = 0x7b7b;
    }
    for (words = (unsigned int near *)&MapA[23][0];
         words <= (unsigned int near *)&MapA[127][0]; words += 0x20) {
        for (word = 0; word < 0x20; ++word)
            words[word] = 0x0303;
    }

    for (row = 23; row <= 127; ++row) {
        for (column = 0; column < 64; ++column) {
            if (SRand1(200) == 0)
                MapA[row][column] = (unsigned char)(SRand1(2) + 0x3e);
        }
    }
    MakeOutletH(2, 25);
    DROPdir = 1;
}
