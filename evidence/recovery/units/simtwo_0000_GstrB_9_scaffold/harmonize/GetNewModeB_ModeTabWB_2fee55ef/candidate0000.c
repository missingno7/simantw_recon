/*
 * GetNewModeB: pick the next behaviour mode for a black ant of the given
 * caste.  Under automatic control (far PACK word ModeAuto == 1) foragers
 * (caste 2) and soldiers (caste 6) draw a random entry from the row of
 * the far signed tables ModeTabWB / ModeTabSB selected by StrategicModeB
 * (rows of eight, column from SRand8, like the verified TurnTab lookup);
 * otherwise those two castes follow the player's ModeMe word.  Every other
 * caste uses its fixed entry in the signed CasteModeTabB table.  The
 * tables and ModeMe live in SIMANT_DATA_GROUP, ModeAuto and StrategicModeB
 * in PACK, all reached through selector slots.
 */
extern int far SRand8(void);
extern int far ModeAuto;
extern int far StrategicModeB;
extern signed char far ModeTabWB[];
extern char far ModeTabSB[][8];
extern char far CasteModeTabB[];
extern int far ModeMe;

int far GetNewModeB(int caste)
{
    if (ModeAuto == 1) {
        if (caste == 2)
            return ModeTabWB[StrategicModeB][SRand8()];
        if (caste == 6)
            return ModeTabSB[StrategicModeB][SRand8()];
    } else if (caste == 2 || caste == 6) {
        return ModeMe;
    }
    return CasteModeTabB[caste];
}
