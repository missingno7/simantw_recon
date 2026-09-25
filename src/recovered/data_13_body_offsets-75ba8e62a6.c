/* Body drawing x/y offsets, followed by the shorter offset pair table. */
int __based(__segname("SIMANT_DATA_GROUP")) BodX[4] = {
    0xecfa, 0xece7, 0xf8fa, 0xf7f6
};
int __based(__segname("SIMANT_DATA_GROUP")) BodY[4] = {
    0xf8f6, 0xecfa, 0xece6, 0xf7fa
};
int __based(__segname("SIMANT_DATA_GROUP")) DBodX[2] = {
    0xebe5, 0xf2f2
};
int __based(__segname("SIMANT_DATA_GROUP")) DBodY[2] = {
    0xf1e7, 0xf6f6
};
