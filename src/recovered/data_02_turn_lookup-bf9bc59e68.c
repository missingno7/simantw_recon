/*
 * Direction stepping tables and their caste conversion lookups.
 * The relative and absolute tables each contain four words; the caste
 * tables contain sixteen flags and eight mapped word values.
 */

int __based(__segname("SIMANT_DATA_GROUP")) relSearchDirs[4] = { 256, 1022, 1532, 2042 };
int __based(__segname("SIMANT_DATA_GROUP")) absSearchDirs[4] = { 256, 767, 1022, 1277 };
int __based(__segname("SIMANT_DATA_GROUP")) IsCarryCaste[16] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0 };
int __based(__segname("SIMANT_DATA_GROUP")) UnCarryCaste[8] = { 512, 514, 516, 1542, 1544, 2826, 3340, 3854 };
