/*
 * CarpetFloorL uses four row-fill runs, then scans the byte offset from
 * row 23 through row 127 inclusive. Each row checks all 64 columns and
 * replaces a cell only when the first random draw is zero.
 */
extern unsigned char near MapA[128 * 64];
extern int far DROPdir;
extern int near SRand1(int range);
extern void near MakeOutletH(int x, int y);

void far CarpetFloorL(void)
{
    unsigned int near *words;
    int word;
    register int off;
    volatile int rowHome;
    int column;

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

    off=23*64;
    rowHome=off;
    while(off<=127*64){
        for(column=0;column<=0x3f;++column)
            if(SRand1(200)==0)MapA[off+column]=(unsigned char)(SRand1(2)+0x3e);
        off+=64;
        rowHome=off;
    }
    MakeOutletH(2, 25);
    DROPdir = 1;
}

/* continuation round 05 pointer/index variant 2 */
