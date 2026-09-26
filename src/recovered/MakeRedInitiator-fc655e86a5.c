/* Clear red initialization; once an eligible red A-list record is found,
 * convert it to an initiator, clear RedTask, mark initialization complete,
 * and stop the scan. */
extern int far RedInitOn;
extern int near BpopT;
extern int far ListIndexA;
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
extern int far RedTask;

void far MakeRedInitiator(void)
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
                RedTask = 0;
                RedInitOn = 1;
                return;
            }
        }
    }
}
