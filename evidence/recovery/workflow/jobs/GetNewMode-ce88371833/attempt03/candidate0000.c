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
        switch (mode) {
        case 2:
            newMode = ModeTabWB[StrategicModeR][SRand8()];
            break;
        case 6:
            newMode = ModeTabSB[StrategicModeR][SRand8()];
            break;
        default:
            newMode = CasteModeTabB[mode];
            break;
        }
    } else if (ModeAuto == 1) {
        switch (mode) {
        case 2:
            newMode = ModeTabWB[StrategicModeB][SRand8()];
            break;
        case 6:
            newMode = ModeTabSB[StrategicModeB][SRand8()];
            break;
        default:
            newMode = CasteModeTabB[mode];
            break;
        }
    } else {
        if (mode == 2 || mode == 6)
            return ModeMe;
        newMode = CasteModeTabB[mode];
    }
    return newMode;
}
