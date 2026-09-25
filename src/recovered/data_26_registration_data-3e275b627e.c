/* Registration name, time marker and fixed-width serial/license placeholders. */
char __based(__segname("SIMANT_DATA_GROUP")) regName[46] =
    "\126\205\366\0YYYYYY";
unsigned long __based(__segname("SIMANT_DATA_GROUP")) regTime = 0x53ed2139UL;
char __based(__segname("SIMANT_DATA_GROUP")) serialStr[20] =
    "XXXXXXXXXXXXXXXXXX" "X";
char __based(__segname("SIMANT_DATA_GROUP")) licenseStr[56] =
    "XXXXXXXXXXXXXXXXXX" "XXXXXXXXXXXXXXXXXX" "XXXXXXXXXXXXXXXXXX";
char __based(__segname("SIMANT_DATA_GROUP")) distribStr[68] =
    "XXXXXXXXXXXXXXXXXX" "XXXXXXXXXXXXXXXXXX" "XXXXXXXXXXXXXXXXXX";
