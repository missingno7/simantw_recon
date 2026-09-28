/* Derived mechanically from the mirrored colony function _GetNewModeR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped GetNewModeR->GetNewMode, StrategicModeR->StrategicModeB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * Hypothesis: modes 2 and 6 select random entries from the two R-side
 * strategic-mode tables.  StrategicModeR[0] is an eight-entry row base;
 * SRand8 supplies the column.  Every other mode is a direct lookup in the
 * caste table.  The far declarations are required by the selector loads
 * before each table access, while the signed int return preserves the
 * target's CWDE conversion of each table byte.
 */
extern int far SRand8(void);
extern int far StrategicModeB[];
extern signed char far ModeTabWB[];
extern signed char far ModeTabSB[];
extern signed char far CasteModeTabB[];

int far GetNewMode(int mode)
{
    if (mode == 2) {
        return ModeTabWB[(StrategicModeB[0] << 3) + SRand8()];
    }
    if (mode == 6) {
        return ModeTabSB[(StrategicModeB[0] << 3) + SRand8()];
    }
    return CasteModeTabB[mode];
}
