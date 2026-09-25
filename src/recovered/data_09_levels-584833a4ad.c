/*
 * Caste and game-mode setup tables.  Each selectable mode retains three
 * packed level masks, preceded by the defaults used by the controls.
 */
int __based(__segname("SIMANT_DATA_GROUP")) IdealCaste[4] = { 60, 40, 0, 0 };
int __based(__segname("SIMANT_DATA_GROUP")) casteBarColors[3] = { 4, 6, 2 };
int __based(__segname("SIMANT_DATA_GROUP")) CasteAuto = 1;
int __based(__segname("SIMANT_DATA_GROUP")) ShowPercentCaste = 1;
int __based(__segname("SIMANT_DATA_GROUP")) casteLevelDefaults[3] = { 0, 0x9999, 0x6666 };
int __based(__segname("SIMANT_DATA_GROUP")) casteSetLevels[4][3] = {
    { 0, 0x9999, 0x6666 },
    { 0x7fff, 0x3fff, 0x3fff },
    { 0, 0xffff, 0 },
    { 0, 0, 0xffff }
};
int __based(__segname("SIMANT_DATA_GROUP")) modeLevelDefaults[3] = { 0x9999, 0x3333, 0x3333 };
int __based(__segname("SIMANT_DATA_GROUP")) modeSetLevels[4][3] = {
    { 0x9999, 0x3333, 0x3333 },
    { 0xffff, 0, 0 },
    { 0, 0xffff, 0 },
    { 0, 0, 0xffff }
};
