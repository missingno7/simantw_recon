/*
 * Point-offset tables for the S, T, T2 and D animation cases.  The final
 * x/y pair supplies the local offset used by the lion point calculation.
 */
int __based(__segname("SIMANT_DATA_GROUP")) PxS[4] = {
    0x0a05, 0x080a, 0xf804, 0xf4f6
};
int __based(__segname("SIMANT_DATA_GROUP")) PyS[4] = {
    0xfdf6, 0x02fc, 0x0207, 0xfbfc
};
int __based(__segname("SIMANT_DATA_GROUP")) PxT[2] = {
    0x0706, 0x0908
};
int __based(__segname("SIMANT_DATA_GROUP")) PyT[2] = {
    0xf0f0, 0xf1f0
};
int __based(__segname("SIMANT_DATA_GROUP")) PxT2[2] = {
    0x0303, 0x0605
};
int __based(__segname("SIMANT_DATA_GROUP")) PyT2[2] = {
    0xeff1, 0xeeee
};
int __based(__segname("SIMANT_DATA_GROUP")) PxD[2] = {
    0x1110, 0x1111
};
int __based(__segname("SIMANT_DATA_GROUP")) PyD[2] = {
    0xfbfa, 0xfdfc
};
int __based(__segname("SIMANT_DATA_GROUP")) PxD2[2] = {
    0x0f0d, 0x1110
};
int __based(__segname("SIMANT_DATA_GROUP")) PyD2[2] = {
    0xf8f8, 0xfaf9
};
int __based(__segname("SIMANT_DATA_GROUP")) Lx[2] = {
    0x0605, 0x0405
};
int __based(__segname("SIMANT_DATA_GROUP")) Ly[2] = {
    0xfdfa, 0x01ff
};
