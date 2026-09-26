/* Clear the red-init flag; if BpopT reaches thirty, convert the first qualifying A-list record, clear RedTask, and mark initialization complete. */
extern int far RedInitOn;
extern int near BpopT;
extern int far ListIndexA;
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
extern int far RedTask;

void far MakeRedInitiator(void) { int index; RedInitOn=0; if (BpopT >= 30) { index=ListIndexA; while(index>0) { --index; if(AlistT[index] > 0x7f) { AlistT[index]=0xb0; AlistM[index]=0x13; AlistS[index]=0; break; } } RedTask=0; RedInitOn=1; } }
