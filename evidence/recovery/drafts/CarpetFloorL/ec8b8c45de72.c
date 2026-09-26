/*
 * CarpetFloorL uses four row-fill runs, then scans the byte offset from
 * row 23 through row 127 inclusive. Each row checks all 64 columns and
 * replaces a cell only when the first random draw is zero.
 */
extern unsigned char near MapA[128 * 64];
extern int far DROPdir;
extern int far SRand1(int range);
extern void far MakeOutletH(int x, int y);

void far CarpetFloorL(void)
{
    unsigned int near *words;
    int word;
    int off;
    int column;
    unsigned char near *row;

    for (words = (unsigned int near *)MapA;
         words <= (unsigned int near *)&MapA[20 * 64]; words += 0x20)
        for (word = 0; word < 0x20; ++word) words[word] = 0x6464;
    for (words = (unsigned int near *)&MapA[21 * 64];
         words <= (unsigned int near *)&MapA[21 * 64]; words += 0x20)
        for (word = 0; word < 0x20; ++word) words[word] = 0x7a7a;
    for (words = (unsigned int near *)&MapA[22 * 64];
         words <= (unsigned int near *)&MapA[23 * 64]; words += 0x20)
        for (word = 0; word < 0x20; ++word) words[word] = 0x7b7b;
    for (words = (unsigned int near *)&MapA[23 * 64];
         words <= (unsigned int near *)&MapA[127 * 64]; words += 0x20)
        for (word = 0; word < 0x20; ++word) words[word] = 0x0303;

    for(off=23*64;off<=127*64;off+=64){row=MapA+off;for(column=0;column<64;++column)if(SRand1(200)==0)*(row+column)=(unsigned char)(SRand1(2)+0x3e);}
    MakeOutletH(2, 25);
    DROPdir = 1;
}

/* continuation round 05 pointer/index variant 2 */
