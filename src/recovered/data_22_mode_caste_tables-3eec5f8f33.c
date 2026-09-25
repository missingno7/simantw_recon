/*
 * The caste and mode controls use byte lookup grids for per-caste choices
 * and word tables for the numeric B variants and automatic mode settings.
 */
unsigned char __based(__segname("SIMANT_DATA_GROUP")) CasteTabC[6][8] = {
    { 2, 2, 2, 2, 2, 6, 6, 6 },
    { 4, 4, 8, 8, 2, 2, 2, 6 },
    { 4, 8, 2, 2, 2, 2, 6, 6 },
    { 2, 2, 2, 2, 2, 6, 6, 6 },
    { 2, 2, 2, 2, 2, 2, 6, 6 },
    { 2, 2, 2, 2, 2, 2, 2, 6 }
};
int __based(__segname("SIMANT_DATA_GROUP")) CasteTabB[4] = { 2, 6, 4, 8 };
int __based(__segname("SIMANT_DATA_GROUP")) ModeTabB[6] = { 2, 4, 1, 7, 12, 6 };
int __based(__segname("SIMANT_DATA_GROUP")) AutoModeTabB[18] = {
    0x0a00, 0x1400, 0x4600, 0x0a14, 0x1e00, 0x0000,
    0x1405, 0x1e1e, 0x0000, 0x0a00, 0x143c, 0x0000,
    0x140a, 0x3200, 0x0000, 0x0000, 0x3c00, 0x0000
};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) ModeTabWB[6][8] = {
    { 1, 2, 7, 7, 7, 7, 7, 7 },
    { 4, 1, 1, 1, 4, 2, 2, 2 },
    { 13, 13, 13, 4, 4, 4, 2, 2 },
    { 13, 13, 4, 4, 4, 4, 4, 2 },
    { 1, 1, 1, 2, 2, 2, 2, 2 },
    { 1, 2, 2, 2, 2, 2, 2, 2 }
};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) ModeTabSB[6][8] = {
    { 7, 7, 7, 7, 7, 7, 7, 7 },
    { 1, 2, 2, 2, 2, 2, 2, 2 },
    { 2, 2, 2, 4, 4, 2, 2, 2 },
    { 2, 4, 4, 4, 4, 4, 4, 2 },
    { 2, 2, 2, 2, 2, 2, 2, 2 },
    { 2, 2, 2, 2, 2, 2, 2, 2 }
};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) CasteModeTabB[2][8] = {
    { 8, 1, 0, 3, 14, 5, 0, 3 },
    { 14, 5, 0, 0, 9, 9, 10, 0 }
};
