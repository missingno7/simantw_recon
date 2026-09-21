/* Resolve actual PACK objects through original NE selector slots and exact MAPSYM names; preserve the observed access widths and body behavior. Names do not by themselves prove types or original source. */
extern unsigned long far BoyMsgCnt;
extern unsigned int far BoyMessOn;
extern unsigned int far BoyMsgOffset;
extern unsigned long far MacTickCount(void);
void SendBoyMsg(int message) {
    if (message <= 22) {
        BoyMsgCnt = MacTickCount() + 300L;
        BoyMessOn = 1;
        BoyMsgOffset = message;
    }
}
