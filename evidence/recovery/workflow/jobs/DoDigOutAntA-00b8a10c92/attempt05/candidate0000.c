/* Update an ant after choosing its random turn, then override it at yard edges. */
extern unsigned char far Dx8[];
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

    x = Dx8[ant + 0x23a4];
    y = Dx8[ant + 0x278e];
    type = Dx8[ant + 0x2f62];
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
            Dx8[ant + 0x2f62] = type;
            return;
        }
        Dx8[ant + 0x2b78] = GetNewMode(caste, type);
        Dx8[ant + 0x334c] = 0;
        return;
    }

    newX = x + Dx8[direction];
    newY = y + Dx8[direction + 8];
    if (Dx8[(newX << 6) + newY + 0x28e8] > Barrier) {
        direction = TurnTab[0][turnOffset + SRand8()];
        type = flags | direction;
        Dx8[ant + 0x2f62] = type;
    }
    Dx8[ant + 0x23a4] = newX;
    Dx8[ant + 0x278e] = newY;
    if (Dx8[ant + 0x334c]) {
        --Dx8[ant + 0x334c];
        if (type & 0x80)
            JamScentRN(newX, newY, Dx8[ant + 0x334c]);
        else
            JamScentBN(newX, newY, Dx8[ant + 0x334c]);
    }
}
