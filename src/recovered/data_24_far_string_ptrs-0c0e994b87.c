/* These loader sites point into named DGROUP text held under lpTimerFunc. */
extern char __based(__segname("DGROUP")) lpTimerFunc[];

char far * __based(__segname("SIMANT_DATA_GROUP")) graphicsName = lpTimerFunc + 6;
char far * __based(__segname("SIMANT_DATA_GROUP")) notEnoughMemoryStr = lpTimerFunc + 9;
char far * __based(__segname("SIMANT_DATA_GROUP")) usageStr = lpTimerFunc + 137;
char far * __based(__segname("SIMANT_DATA_GROUP")) configFileMissingStr = lpTimerFunc + 190;
char far * __based(__segname("SIMANT_DATA_GROUP")) configFileName = lpTimerFunc + 224;
char far * __based(__segname("SIMANT_DATA_GROUP")) helpFileName = lpTimerFunc + 235;
