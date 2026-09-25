/*
 * Current tutorial, menu, map editor and speed-control state.  The final
 * byte-sized table lists the four speed choices in display order.
 */
int __based(__segname("SIMANT_DATA_GROUP")) CurGndTileID = 1000;
int __based(__segname("SIMANT_DATA_GROUP")) TutorCnt = 0;
int __based(__segname("SIMANT_DATA_GROUP")) TutLesson = 1;
int __based(__segname("SIMANT_DATA_GROUP")) TutGiven = 0;
int __based(__segname("SIMANT_DATA_GROUP")) OptionStates[7] = { 0, 1, 1, 1, 1, 0, 0 };
signed char __based(__segname("SIMANT_DATA_GROUP")) ExpSubStates[8] = { -1, 0, 0, 0, 0, 0, 0, -1 };
int __based(__segname("SIMANT_DATA_GROUP")) MapPlane2EditTab[4] = { 0, 0, 1, 2 };
int __based(__segname("SIMANT_DATA_GROUP")) MapMode = 1;
int __based(__segname("SIMANT_DATA_GROUP")) BorderFlag = 1;
int __based(__segname("SIMANT_DATA_GROUP")) GameSpeed = 1;
int __based(__segname("SIMANT_DATA_GROUP")) SpeedDelayVals[4] = { 6, 2, 0, -1 };
unsigned char __based(__segname("SIMANT_DATA_GROUP")) GameSpeedTab[4] = { 0, 1, 2, 3 };
