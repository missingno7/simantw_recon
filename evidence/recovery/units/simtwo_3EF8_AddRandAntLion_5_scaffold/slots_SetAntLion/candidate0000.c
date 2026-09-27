/* Resolve actual PACK objects through original NE selector slots and exact MAPSYM names; preserve the observed access widths and body behavior. Names do not by themselves prove types or original source. */
extern unsigned char far LionListX[];
extern unsigned char far LionListY[];
extern unsigned char far LionListT[];
extern void far SetMap(int plane,int x,int y,int value);
void SetAntLion(int index) {
    SetMap(1,LionListX[index],LionListY[index],LionListT[index]+0x38);
}
