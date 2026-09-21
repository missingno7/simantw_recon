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
        strat = ModeTabWB[strat][SRand8()];
    else if (mode == 6)
        strat = ModeTabSB[strat][SRand8()];
    else
        strat = CasteModeTabB[mode];
    return strat;
}
