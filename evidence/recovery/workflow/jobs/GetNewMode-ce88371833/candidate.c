extern int far SRand8(void);
extern char far ModeTabWB[][8];
extern char far ModeTabSB[][8];
extern char far CasteModeTabB[];
extern int far StrategicModeR;
extern int far StrategicModeB;
extern int far ModeAuto;
extern int far ModeMe;

int far GetNewMode(int mode, int flags)
{
    int newMode;

    if (flags & 0x80) {
        if (mode == 2)
            newMode = ModeTabWB[StrategicModeR][SRand8()];
        else if (mode == 6)
            newMode = ModeTabSB[StrategicModeR][SRand8()];
        else
            newMode = CasteModeTabB[mode];
    } else if (ModeAuto == 1) {
        if (mode == 2)
            newMode = ModeTabWB[StrategicModeB][SRand8()];
        else if (mode == 6)
            newMode = ModeTabSB[StrategicModeB][SRand8()];
        else
            newMode = CasteModeTabB[mode];
    } else {
        if (mode == 2 || mode == 6)
            return ModeMe;
        newMode = CasteModeTabB[mode];
    }
    return newMode;
}
