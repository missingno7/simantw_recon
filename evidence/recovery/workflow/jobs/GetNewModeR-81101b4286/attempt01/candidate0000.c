/*
 * Hypothesis: modes 2 and 6 select random entries from the two R-side
 * strategic-mode tables.  StrategicModeR[0] is an eight-entry row base;
 * SRand8 supplies the column.  Every other mode is a direct lookup in the
 * caste table.  The far declarations are required by the selector loads
 * before each table access, while the signed int return preserves the
 * target's CWDE conversion of each table byte.
 */
extern int far SRand8(void);
extern int far StrategicModeR[];
extern unsigned char far ModeTabWB[];
extern unsigned char far ModeTabSB[];
extern unsigned char far CasteModeTabB[];

int far GetNewModeR(int mode)
{
    int row;

    if (mode == 2) {
        row = SRand8();
        return ModeTabWB[(StrategicModeR[0] << 3) + row];
    }
    if (mode == 6) {
        row = SRand8();
        return ModeTabSB[(StrategicModeR[0] << 3) + row];
    }
    return CasteModeTabB[mode];
}
