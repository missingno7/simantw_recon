/* Trap and eating point coordinates with their adjacent MR lookup words. */
int __based(__segname("SIMANT_DATA_GROUP")) LionTrapPnts[8] = {
    0, 0, 0x26, 0x27, 0x26, 0x34, 0x26, 0x34
};
int __based(__segname("SIMANT_DATA_GROUP")) YellowEatPnt[2] = {
    0x48, 0x3e
};
int __based(__segname("SIMANT_DATA_GROUP")) MRtab[7] = {
    0x0103, 0x0303, 0x0202, 0x0504, 0x0106, 0x0404, 0x0006
};
