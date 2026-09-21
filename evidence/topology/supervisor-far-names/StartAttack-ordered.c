/* Resolve actual PACK objects through original NE selector slots and exact MAPSYM names; preserve the observed access widths and body behavior. Names do not by themselves prove types or original source. */
extern unsigned int far * far AdviceStrs;
extern unsigned int far JustToBeMean;
extern int far SRand1(unsigned int range);
extern void far myBeginSong(unsigned int song, unsigned int mode);
extern void far EditMessage(int first,int second,int width,int fourth,int fifth);
void StartAttack(void) {
    JustToBeMean = SRand1(100) + 30;
    myBeginSong(0x2b0a,0x3f);
    EditMessage(AdviceStrs[10],AdviceStrs[11],0x78,0,0);
}
