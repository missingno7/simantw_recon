/*
 * The save-game caption and error/help prompt fragments are fixed-size
 * strings.  Their legacy leading p tag and 0xAA mark are stored as bytes.
 */

char __based(__segname("SIMANT_DATA_GROUP")) GAME_FILE[256] = "pSimAnt\252 Saved Game";
char __based(__segname("SIMANT_DATA_GROUP")) nilPStr[2] = "p";
char __based(__segname("SIMANT_DATA_GROUP")) ErrStr[10] = "pError!!";
char __based(__segname("SIMANT_DATA_GROUP")) AlertSimAntFastPStr[30] = "pNOTE: SimAnt\252 runs radically";
char __based(__segname("SIMANT_DATA_GROUP")) in16colorPStr[28] = "p  faster in 16-color mode!";
char __based(__segname("SIMANT_DATA_GROUP")) PleaseRefToPStr[22] = "pPlease refer to the";
char __based(__segname("SIMANT_DATA_GROUP")) theSimAntManPStr[18] = "pSimAnt\252 manual.";
char __based(__segname("SIMANT_DATA_GROUP")) SaveEnvPromptPStr[16] = "pSave Game As:";
char __based(__segname("SIMANT_DATA_GROUP")) SimAntResrvPStr[32] = "pThe name 'SimAnt\252' is reserved";
char __based(__segname("SIMANT_DATA_GROUP")) forthisAppPStr[24] = "pfor this application.";
