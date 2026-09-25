/*
 * Colony and terrain storage.  Exit and pheromone fields are 64 by 64
 * or 64 by 32 byte grids; the Alist/Blist/Rlist arrays hold the parallel
 * ant coordinates and attributes used by each colony.  All begin empty.
 */

int __based(__segname("SIMANT_DATA_GROUP")) YMapPopB[96] = {0};
int __based(__segname("SIMANT_DATA_GROUP")) YMapPopR[96] = {0};
int __based(__segname("SIMANT_DATA_GROUP")) YMapSeeds[16][12] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) ExitMapB[64][64] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) ExitMapR[64][64] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[1002] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[1002] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[1002] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[1002] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[1002] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistX[502] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistY[502] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistM[502] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistT[502] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistS[502] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistX[502] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistY[502] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistM[502] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistT[502] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistS[502] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) TemDensity[64][32] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapA[64][32] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapF[64][32] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapBN[64][32] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapBT[64][32] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapRN[64][32] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapRT[64][32] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) HoleMapB[64] = {0};
unsigned char __based(__segname("SIMANT_DATA_GROUP")) HoleMapR[64] = {0};
