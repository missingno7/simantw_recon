/* GetNewMode: choose the new caste mode from the red strategy, the automatic
 * black strategy, or the current mode table. Special castes 2 and 6 use
 * their corresponding eight-way strategy table; other castes use the direct
 * CasteModeTabB entry. */
extern int far SRand8(void);
extern unsigned char far ModeTabWB[][8];
extern unsigned char far ModeTabSB[][8];
extern unsigned char far CasteModeTabB[];
extern int far StrategicModeR;
extern int far StrategicModeB;
extern int far ModeAuto;
extern int far ModeMe;

int far GetNewMode(int caste, int type)
{
    int row;
    int random;
    int result;

    if (type & 0x80) {
        if (caste == 2) {
            row = StrategicModeR;
            random = SRand8();
            result = ModeTabWB[row][random];
        } else if (caste == 6) {
            row = StrategicModeR;
            random = SRand8();
            result = ModeTabSB[row][random];
        } else {
            result = CasteModeTabB[caste];
        }
    } else if (ModeAuto == 1) {
        if (caste == 2) {
            row = StrategicModeB;
            random = SRand8();
            result = ModeTabWB[row][random];
        } else if (caste == 6) {
            row = StrategicModeB;
            random = SRand8();
            result = ModeTabSB[row][random];
        } else {
            result = CasteModeTabB[caste];
        }
    } else if (caste == 2 || caste == 6) {
        result = ModeMe;
    } else {
        result = CasteModeTabB[caste];
    }

    return result;
}
