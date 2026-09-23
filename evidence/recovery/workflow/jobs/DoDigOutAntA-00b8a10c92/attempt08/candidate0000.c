/* Update an ant after choosing its random turn, then override it at yard edges. */
extern unsigned char far Dx8[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
extern char far TurnTab[][8];
extern int far SRand8(void);
extern int far Bounce(int x, int y);
extern int far GetNewMode(int caste, int type);
extern int far Barrier;
extern void near JamScentBN(int x, int y, int scent);
extern void near JamScentRN(int x, int y, int scent);

void near DoDigOutAntA(int ant)
{
    int x;
    int y;
    int type;
    int caste;
    int flags;
    int turnOffset;
    int direction;
    int newX;
    int newY;
    int bounced;

    x = AlistX[ant];
    y = AlistY[ant];
    type = AlistT[ant];
    flags = type & 0xf8;
    caste = (type & 0x78) >> 3;
    turnOffset = (type & 7) << 3;
    direction = TurnTab[0][turnOffset + SRand8()];
    bounced = Bounce(x, y);
    if (bounced) {
        direction = (bounced - 1) & 7;
        newX = x + Dx8[direction];
        newY = y + Dx8[direction + 8];
        if (caste == 5 || caste == 9) {
            direction = TurnTab[0][turnOffset + SRand8()];
            type = flags | direction;
            AlistT[ant] = type;
            return;
        }
        AlistM[ant] = GetNewMode(caste, type);
        AlistS[ant] = 0;
        return;
    }

    newX = x + Dx8[direction];
    newY = y + Dx8[direction + 8];
    if (Dx8[(newX << 6) + newY + 0x28e8] > Barrier) {
        direction = TurnTab[0][turnOffset + SRand8()];
        type = flags | direction;
        AlistT[ant] = type;
    }
    AlistX[ant] = newX;
    AlistY[ant] = newY;
    if (AlistS[ant]) {
        --AlistS[ant];
        if (type & 0x80)
            JamScentRN(newX, newY, AlistS[ant]);
        else
            JamScentBN(newX, newY, AlistS[ant]);
    }
}



