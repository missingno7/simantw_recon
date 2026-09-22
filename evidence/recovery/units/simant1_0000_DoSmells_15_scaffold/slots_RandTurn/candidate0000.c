/* Byte-matched C reconstruction. Modern filename and isolated translation unit.
 * Historical source text and declaration spelling are not uniquely recovered. */
extern int far SRand8(void);
extern char far TurnTab[8][8];
int near RandTurn(int d) { return TurnTab[d][SRand8()]; }
