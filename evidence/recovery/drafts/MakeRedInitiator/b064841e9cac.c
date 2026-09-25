extern int far RedInitOn;
extern int near BpopT;
extern int far ListIndexA;
extern unsigned char far AlistT[];
extern unsigned char far AlistM[];
extern unsigned char far AlistS[];
extern int far RedTask;

void MakeRedInitiator(void)
{
    int index;

    RedInitOn = 0;
    if (BpopT >= 30) {
        index = ListIndexA;
        while (index > 0) {
            --index;
            if (AlistT[index] > 0x7f) {
                AlistT[index] = 0xb0;
                AlistM[index] = 0x13;
                AlistS[index] = 0;
            }
        }
        RedTask = 0;
        RedInitOn = 1;
    }
}
