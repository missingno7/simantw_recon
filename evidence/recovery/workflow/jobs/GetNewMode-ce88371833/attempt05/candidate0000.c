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
    int strat;
    int newMode;

    if (flags & 0x80)
        strat = StrategicModeR;
    else if (ModeAuto == 1)
        strat = StrategicModeB;
    else {
        if (mode == 2 || mode == 6)
            return ModeMe;
        return CasteModeTabB[mode];
    }
    if (mode == 2)
        newMode = ModeTabWB[strat][SRand8()];
    else if (mode == 6)
        newMode = ModeTabSB[strat][SRand8()];
    else
        newMode = CasteModeTabB[mode];
    return newMode;
}
